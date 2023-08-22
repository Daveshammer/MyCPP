//反应堆简单版
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <sys/epoll.h>
#include "wrap.h"

#define _BUF_LEN_  1024
#define _EVENT_SIZE_ 1024

// 全局epoll树的根
int gepfd = 0;

// 事件驱动结构体
typedef struct xx_event {
    int fd; // 事件对应的文件描述符
    int events; // 事件类型 EPOLLIN EPOLLOUT
    void (*call_back)(int fd, int events, void *arg); // 事件发生时要调用的回调函数
    void *arg; // 回调函数的参数
    char buf[_BUF_LEN_]; 
    int buflen; // 缓冲区中数据的长度
    int epfd; // 事件所属的epoll树的根
}xevent;

xevent myevents[_EVENT_SIZE_ + 1];

void readData(int fd, int events, void *arg);

// 添加事件
//eventadd(lfd,EPOLLIN,initAccept,&myevents[_EVENT_SIZE_],&myevents[_EVENT_SIZE_]);
void eventadd(int fd, int events, void (*call_back)(int, int, void *), void *arg, xevent *ev)
{
    ev->fd = fd;
    ev->events = events;
    ev->call_back = call_back;

    struct epoll_event epv; // 内核事件结构体
    epv.events = events; // 事件类型 EPOLLIN EPOLLOUT
    epv.data.ptr = ev; // 将事件驱动结构体指针传递给内核
    epoll_ctl(gepfd, EPOLL_CTL_ADD, fd, &epv); // 将事件添加到epoll树上
}

// 修改事件
//eventset(fd,EPOLLOUT,senddata,arg,ev);
void eventset(int fd, int events, void (*call_back)(int, int, void *), void *arg, xevent *ev)
{
    ev->fd = fd;
    ev->events = events;
    ev->call_back = call_back;

    struct epoll_event epv; // 内核事件结构体
    epv.events = events; // 事件类型 EPOLLIN EPOLLOUT
    epv.data.ptr = ev; // 将事件驱动结构体指针传递给内核
    epoll_ctl(gepfd, EPOLL_CTL_MOD, fd, &epv); // 修改
}

// 删除事件
void eventdel(xevent *ev, int fd, int events)
{
    printf("begin call %s\n", __FUNCTION__);

    ev->fd = 0;
    ev->events = 0;
    ev->call_back = NULL;
    memset(ev->buf, 0x00, sizeof(ev->buf));
    ev->buflen = 0;

    struct epoll_event epv;
    epv.data.ptr = NULL;
    epv.events = events; // 事件类型 EPOLLIN EPOLLOUT
    epoll_ctl(gepfd, EPOLL_CTL_DEL, fd, &epv); // 下树
}

// 发送数据
void senddata(int fd, int events, void *arg)
{
    printf("begin call %s\n", __FUNCTION__);

    xevent *ev = (xevent *)arg;
    Write(fd, ev->buf, ev->buflen); // buf写到fd
    eventset(fd, EPOLLIN, readData, arg, ev); // 发送完数据后，修改事件为读
}

// 读数据
void readData(int fd, int events, void *arg)
{
    printf("begin call %s\n", __FUNCTION__);
    xevent *ev = (xevent *)arg;

    ev->buflen = Read(fd, ev->buf, sizeof(ev->buf)); // 读取数据到buf
    if (ev->buflen > 0) // 读到数据，准备发送
    {
        eventset(fd, EPOLLOUT, senddata, arg, ev);
    }
    else if (ev->buflen == 0) // 对方关闭连接
    {
        Close(fd);
        eventdel(ev, fd, EPOLLIN);
    }
}

// 新连接处理
void initAccept(int fd, int events, void *arg)
{
    printf("begin call %s, gepfd = %d\n", __FUNCTION__, gepfd); 

    int i;
    struct sockaddr_in addr;
    socklen_t len = sizeof(addr);

    int cfd = Accept(fd, (struct sockaddr *)&addr, &len);

    // 查找myevents数组中可用的位置
    for (i = 0; i < _EVENT_SIZE_; i++)
    {
        if (myevents[i].fd == 0) // 找到可用位置就跳出循环
        {
            break;
        }
    }

    // 设置读事件
    eventadd(cfd, EPOLLIN, readData, &myevents[i], &myevents[i]);
}

int main()
{
    // 创建socket
    int lfd = Socket(AF_INET, SOCK_STREAM, 0);

    // 端口复用
    int opt = 1;
    setsockopt(lfd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));

    // 绑定
    struct sockaddr_in servaddr;
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(8888);
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    Bind(lfd, (struct sockaddr *)&servaddr, sizeof(servaddr));

    // 监听
    Listen(lfd, 128);

    // 创建epoll树的根
    gepfd = epoll_create(1024);
    printf("gepfd === %d\n", gepfd);

    struct epoll_event events[_EVENT_SIZE_]; // 用于存放epoll_wait返回的就绪事件

    // 添加最初始事件，将监听的描述符上树
    eventadd(lfd, EPOLLIN, initAccept, &myevents[_EVENT_SIZE_], &myevents[_EVENT_SIZE_]);

    while (1)
    {
        int nready = epoll_wait(gepfd, events, _EVENT_SIZE_, -1); // 监听事件
        if (nready < 0)
        {
            perror("epoll_wait error");
            exit(1);
        }
        else if (nready > 0) // 调用epoll_wait成功，返回有事件发生的文件描述符的个数
        {
            int i = 0;
            for (int i = 0; i < nready; i++)
            {
                xevent *xe = (xevent *)events[i].data.ptr; // 获取内核事件结构体指针
                printf("fd = %d\n", xe->fd);

                if (xe->events & events[i].events)
                {
                    xe->call_back(xe->fd, events[i].events, xe->arg); // 调用回调函数处理事件(读写
                }
            }
        }
    }
    Close(lfd);

    return 0;
}