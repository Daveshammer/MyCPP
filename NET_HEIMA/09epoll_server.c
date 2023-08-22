#include <stdio.h>
#include <fcntl.h>
#include <sys/epoll.h>

#include "wrap.h"

/**
 * gcc 06select.c  wrap.c
 * nc 127.0.0.1 8888
*/

int main()
{
    // 创建套接字 绑定
    int lfd = tcp4bind(8888, NULL);
    // 监听
    Listen(lfd, 128);
    // 创建树
    int epfd = epoll_create(1);
    // 将lfd上树
    struct epoll_event ev, evs[1024];
    ev.data.fd = lfd;
    ev.events = EPOLLIN;
    epoll_ctl(epfd, EPOLL_CTL_ADD, lfd, &ev);
    // while监听
    while (1)
    {
        int nready = epoll_wait(epfd, evs, 1024, -1); // 返回发生事件的数量，事件写到evs中
        printf("epoll wait _______________\n");
        if (nready < 0)
        {
            perror("");
            break;
        }
        else if (nready == 0) // 没有文件描述符变化
        {
            continue;
        }
        else // 有文件描述符变化
        {
            for (int i = 0; i < nready; i++)
            {
                // 判断lfd变化，并且是读事件变化
                if (evs[i].data.fd == lfd && evs[i].events & EPOLLIN)
                {
                    struct sockaddr_in cliaddr;
                    char ip[16] = "";
                    socklen_t len = sizeof(cliaddr);
                    int cfd = Accept(lfd, (struct sockaddr*)&cliaddr, &len);

                    printf("new client ip=%s port=%d\n", inet_ntop(AF_INET, &cliaddr.sin_addr.s_addr, ip, 16),
                        ntohs(cliaddr.sin_port));
                    // 将cfd上树
                    ev.data.fd = cfd;
                    // ev.events = EPOLLIN; // 默认为水平触发
                    ev.events = EPOLLIN | EPOLLET; // 设置为边缘触发
                    epoll_ctl(epfd, EPOLL_CTL_ADD, cfd, &ev);
                }
                else if (evs[i].events & EPOLLIN) // cfd变化
                {
                    while (1) // 以4字节循环读取数据，直到读完
                    {
                        char buf[4] = "";
                        // 如果读一个缓冲区，缓冲区没有数据，如果是阻塞的，就会阻塞等待，
                        // 如果是非阻塞的，就会返回-1，并将errno设置为EAGAIN
                        int n = read(evs[i].data.fd, buf, sizeof(buf));
                        if (n < 0) // 出错，cfd下树
                        {
                            // 如果缓冲区读干净了，跳出while，继续监听
                            if (errno == EAGAIN)
                            {
                                break;
                            }
                            // 其他错误，cfd下树
                            perror("");
                            close(evs[i].data.fd);
                            epoll_ctl(epfd, EPOLL_CTL_DEL, evs[i].data.fd, &evs[i]);
                            break;
                        }
                        else if (n == 0) // 客户端关闭，cfd下树
                        {
                            printf("client close\n");
                            close(evs[i].data.fd);
                            epoll_ctl(epfd, EPOLL_CTL_DEL, evs[i].data.fd, &evs[i]);
                            break;
                        }
                        else
                        {
                            // printf("recv buf=%s\n", buf);
                            write(STDOUT_FILENO, buf, n);
                            write(evs[i].data.fd, buf, n);
                        }
                    }
                }
            }
        }
    }


    return 0;
}