/*
 * epoll基于非阻塞I/O事件驱动
 */
#include <stdio.h>
#include <sys/socket.h>
#include <sys/epoll.h>
#include <arpa/inet.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#define MAX_EVENTS 1024 // 监听上限数
#define BUFLEN 4096
#define SERV_PORT 8080

/*描述就绪文件描述符相关信息*/
struct myevent_s
{
    int fd;                                           // 要监听的文件描述符
    int events;                                       // 对应的监听事件 EPOLLIN EPOLLOUT
    void *arg;                                        // 泛型参数
    void (*call_back)(int fd, int events, void *arg); // 回调函数
    int status;                                       // 是否在监听：1->在红黑树上(监听), 0->不在(不监听)
    char buf[BUFLEN];                                 // 读缓冲区
    int len;
    long last_active; // 记录每次加入红黑树 g_efd 的时间值
};

int g_efd;                                 // 全局变量，红黑树根节点
struct myevent_s g_events[MAX_EVENTS + 1]; // 自定义结构体类型数组. +1-->listen fd

/*将结构体 myevent_s 成员变量初始化*/
void eventset(struct myevent_s *ev, int fd, void (*call_back)(int, int, void *), void *arg)
{
    ev->fd = fd;
    ev->call_back = call_back;
    ev->events = 0;
    ev->arg = arg;
    ev->status = 0;
    // bzero(ev->buf, sizeof(ev->buf));
    // ev->len = 0;
    ev->last_active = time(NULL);

    return;
}

/*向epoll监听的红黑树 添加一个 文件描述符*/
void eventadd(int efd, int events, struct myevent_s *ev)
{
    struct epoll_event epv = {0, {0}};
    int op;
    epv.data.ptr = ev;
    epv.events = ev->events = events; // EPOLLIN EPOLLOUT

    if (ev->status == 1) // 已经在红黑树 g_efd 上
    {
        op = EPOLL_CTL_MOD;
    }
    else // 不在红黑树 g_efd 上
    {
        op = EPOLL_CTL_ADD;
        ev->status = 1;
    }

    if (epoll_ctl(efd, op, ev->fd, &epv) < 0) // 实际添加/修改
        printf("event add failed [fd=%d], events[%d]\n", ev->fd, events);
    else
        printf("event add OK [fd=%d], op=%d, events[%0X]\n", ev->fd, op, events);

    return;
}

/*从epoll监听的红黑树中删除一个文件描述符*/
void eventdel(int efd, struct myevent_s *ev)
{
    struct epoll_event epv = {0, {0}};

    if (ev->status != 1) // 不在红黑树上
        return;

    epv.data.ptr = ev;
    ev->status = 0;                              // 修改状态，表示不监听
    epoll_ctl(efd, EPOLL_CTL_DEL, ev->fd, &epv); // 从红黑树efd上删除ev->fd
}

/*当有文件描述符就绪，epoll返回，调用该函数 与客户端建立连接*/
// 回调函数 - 监听的文件描述符发送读事件时被调用
void acceptconn(int lfd, int events, void *arg)
{
    struct sockaddr_in cin;
    socklen_t len = sizeof(cin);
    int cfd, i;

    if ((cfd = accept(lfd, (struct socketaddr *)&cin, &len)) == -1)
    {
        if (errno != EAGAIN && errno != EINTR)
        {
            /*暂时不做出错处理*/
        }
        printf("%s: accept, %s\n", __func__, strerror(errno));
        return;
    }

    do
    {
        for (i = 0; i < MAX_EVENTS; i++) // 从全局数组g_events中找一个空闲元素
        {
            if (g_events[i].status == 0)
                break;
        }
        if (i == MAX_EVENTS) // 没有空闲元素
        {
            printf("%s: max connect limit[%d]\n", __func__, MAX_EVENTS);
            break;
        }

        int flag = 0;
        if ((flag = fcntl(cfd, F_SETFL, O_NONBLOCK)) < 0) // 将cfd设置为非阻塞
        {
            printf("%s: fcntl nonblocking failed, %s\n", __func__, strerror(errno));
            break;
        }

        /*给cfd设置一个myevent_s结构体，回调函数 设置为 recvdata*/
        eventset(&g_events[i], cfd, recvdata, &g_events[i]); // 建立连接之后，准备接收数据
        eventadd(g_efd, EPOLLIN, &g_events[i]);              // 将cfd添加到红黑树g_efd上，监听读事件
    } while (0);

    printf("new connect [%s:%d][time:%ld], pos[%d]\n",
           inet_ntoa(cin.sin_addr), ntohs(cin.sin_port), g_events[i].last_active, i);
    return;
}

// 回调函数 - 通信的文件描述符发生读事件时被调用
void recvdata(int fd, int events, void *arg)
{
    struct myevent_s *ev = (struct myevent_s *)arg;
    int len;

    len = recv(fd, ev->buf, sizeof(ev->buf), 0); // 读文件描述符，将数据放入ev->buf中

    eventdel(g_efd, ev); // 先从红黑树g_efd上删除该文件描述符，读到数据后面再重新上树

    if (len > 0)
    {
        ev->len = len;
        ev->buf[len] = '\0'; // 读到的数据添加结束符
        printf("C[%d]:%s\n", fd, ev->buf);

        eventset(ev, fd, senddata, ev); // 接收数据后准备发送
        eventadd(g_efd, EPOLLOUT, ev);  // 将该文件描述符添加到红黑树g_efd上，监听写事件
    }
    else if (len == 0)
    {
        close(ev->fd);
        /* ev-g_events 地址相减得到偏移元素位置 */
        printf("[fd=%d] pos[%ld], closed\n", fd, ev - g_events);
    }
    else
    {
        close(ev->fd);
        printf("recv[fd=%d] error[%d]:%s\n", fd, errno, strerror(errno));
    }
    return;
}

// 回调函数 - 通信的文件描述符发生写事件时候被调用
void senddata(int fd, int events, void *arg)
{
    struct myevent_s *ev = (struct myevent_s *)arg;
    int len;

    /*
    printf("fd=%d\tev->buf=%s\ttev->len=%d\n", fd, ev->buf, ev->len);
    printf("send len = %d\n", len);
    */
    if (len > 0)
    {
        printf("send[fd=%d], [%d]%s\n", fd, len, ev->buf);
        eventdel(g_efd, ev);            // 从红黑树g_efd中移除
        eventset(ev, fd, recvdata, ev); // 将该fd的回调函数改为recvdata
        eventadd(g_efd, EPOLLIN, ev);   // 将该fd添加到红黑树g_efd上，监听读事件
    }
    else
    {
        close(ev->fd);       // 关闭连接
        eventdel(g_efd, ev); // 从红黑树g_efd中移除
        printf("send[fd=%d] error %s\n", fd, strerror(errno));
    }
    return;
}

/*创建socket，初始化lfd*/
void initlistensocket(int efd, short port)
{
    int lfd = socket(AF_INET, SOCK_STREAM, 0);
    fcntl(lfd, F_SETFL, O_NONBLOCK); // 将lfd设置为非阻塞

    eventset(&g_events[MAX_EVENTS], lfd, acceptconn, &g_events[MAX_EVENTS]); // 设置lfd的回调函数为acceptconn
    eventadd(efd, EPOLLIN, &g_events[MAX_EVENTS]);                           // 将lfd添加到红黑树efd上，监听读事件

    struct sockaddr_in sin;
    memset(&sin, 0, sizeof(sin));
    sin.sin_family = AF_INET;
    sin.sin_addr.s_addr = INADDR_ANY;
    sin.sin_port = htons(port);

    bind(lfd, (struct sockaddr *)&sin, sizeof(sin));

    listen(lfd, 20);

    return;
}

int main(int argc, char *argv[])
{
    unsigned short port = SERV_PORT;

    if (argc == 2)
        port = atoi(argv[1]);

    g_efd = epoll_create(MAX_EVENTS + 1); // 创建红黑树，返回全局g_efd
    if (g_efd <= 0)
        printf("cteate efd in %s err %s\n", __func__, strerror(errno));

    initlistensocket(g_efd, port); // 初始化监听socket

    struct epoll_event events[MAX_EVENTS + 1]; // 用于存放epoll_wait返回的就绪事件
    printf("server running:port[%d]\n", port);

    int checkpos = 0, i;
    while (1)
    {
        /* 超时验证，每次测试100个链接，不测试listenfd 当客户端60秒内没有和服务器通信，则关闭此客户端链接 */
        long now = time(NULL);
        for (i = 0; i < 100; i++, checkpos++) // 一次循环检测100个，使用checkpos控制检测对象
        {
            if (checkpos == MAX_EVENTS)
                checkpos = 0;
            if (g_events[checkpos].status != 1) // 不在红黑树g_efd上
                continue;

            long duration = now - g_events[checkpos].last_active; // 客户端不活跃的时间
            if (duration >= 60)
            {
                close(g_events[checkpos].fd); // 关闭客户端链接
                printf("[fd=%d] timeout\n", g_events[checkpos].fd);
                eventdel(g_efd, &g_events[checkpos]); // 从红黑树g_efd中移除
            }
        }

        /*监听红黑树g_efd，将满足的事件的文件描述符加至events数据中，1秒没有事件满足，返回 0*/
        int nfd = epoll_wait(g_efd, events, MAX_EVENTS + 1, 1000);
        if (nfd < 0)
        {
            printf("epoll_wait error, exit\n");
            break;
        }

        for (i = 0; i < nfd; i++)
        {
            /*使用自定义结构体myevent_s类型指针，接收 联合体data和void *ptr成员*/
            struct myevent_s *ev = (struct myevent_s *)events[i].data.ptr;

            if ((events[i].events & EPOLLIN) && (ev->events & EPOLLIN)) // 读就绪事件
            {
                ev->call_back(ev->fd, events[i].events, ev->arg);
            }
            if ((events[i].events & EPOLLOUT) && (ev->events & EPOLLOUT))
            {
                ev->call_back(ev->fd, events[i].events, ev->arg);
            }
        }
    }

    /*退出前释放所有资源*/

    return 0;
}