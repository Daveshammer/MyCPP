#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <iostream>
#include <string.h>
#include <sys/time.h>
#include <vector>
#include <errno.h>

/*
    int select(int nfds, fd_set *readfds, fd_set *writefds, fd_set *exceptfds, struct timeval *timeout);

    参数 nfds， Linux 下 socket 也称 fd，这个参数的值设置成所有需要使用 select 函数检测事件的 fd 中的最大 fd 值加 1。
    参数 readfds，需要监听可读事件的 fd 集合。
    参数 writefds，需要监听可写事件的 fd 集合。
    参数 exceptfds，需要监听异常事件 fd 集合。
*/

// 自定义代表无效fd的值
#define INVALID_FD -1

int main(int argc, char *argv[])
{
    // 1.创建一个侦听socket
    int listenfd = socket(AF_INET, SOCK_STREAM, 0);
    if (listenfd == INVALID_FD)
    {
        std::cout << "create listen socket error." << std::endl;
        return -1;
    }

    // 2.初始化服务器地址
    struct sockaddr_in bindaddr;
    bindaddr.sin_family = AF_INET;
    bindaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    bindaddr.sin_port = htons(3000);
    if (bind(listenfd, (struct sockaddr *)&bindaddr, sizeof(bindaddr)) == -1)
    {
        std::cout << "bind listen socket error." << std::endl;
        close(listenfd);
        return -1;
    }

    // 3.启动侦听
    if (listen(listenfd, SOMAXCONN) == -1)
    {
        std::cout << "listen error." << std::endl;
        close(listenfd);
        return -1;
    }

    // 存储客户端socket的数组
    std::vector<int> clientfds;
    int maxfd;

    while (true)
    {
        fd_set readset;
        FD_ZERO(&readset);

        // 将侦听socket加入到待检测的可读事件中去
        FD_SET(listenfd, &readset);

        maxfd = listenfd;
        // 将客户端fd加入到待检测的可读事件中去
        int clientfdslength = clientfds.size();
        for (int i = 0; i < clientfdslength; ++i)
        {
            if (clientfds[i] != INVALID_FD)
            {
                FD_SET(clientfds[i], &readset);

                if (maxfd < clientfds[i])
                    maxfd = clientfds[i];
            }
        }

        /*
            select 函数的 timeval 结构体的 tv_sec 和 tv_usec 如果两个值设置为 0，即检测事件总时间设置为 0，
            其行为是 select 会检测一下相关集合中的 fd，如果没有需要的事件，则立即返回
        */
        timeval tm;
        tm.tv_sec = 5; // 设置select函数的超时时间为5秒
        tm.tv_usec = 0;
        // 4.select，暂且只检测可读事件，不检测可写和异常事件
        int ret = select(maxfd + 1, &readset, NULL, NULL, &tm);
        if (ret == -1)
        {
            // 出错，退出程序。
            if (errno != EINTR)
                break;
        }
        else if (ret == 0)
        {
            // select 函数超时，下次继续
            std::cout << "no event in specific time interval." << std::endl;
            continue;
        }
        else
        {
            // 5.根据不同类型fd，做不同处理
            if (FD_ISSET(listenfd, &readset)) // listenfd有事件，说明有新的连接到来
            {
                // 侦听socket的可读事件，则表明有新的连接到来
                struct sockaddr_in clientaddr;
                socklen_t clientaddrlen = sizeof(clientaddr);
                // 接受客户端连接
                int clientfd = accept(listenfd, (struct sockaddr *)&clientaddr, &clientaddrlen);
                if (clientfd == INVALID_FD)
                {
                    // 接受连接出错，退出程序
                    break;
                }

                // 只接受连接，不调用recv收取任何数据
                std::cout << "accept a client connection, fd: " << clientfd << std::endl;
                clientfds.push_back(clientfd);
            }
            else // clientfd 有事件，则表明有数据到来，调用recv收取数据
            {
                // 假设对端发来的数据长度不超过63个字符
                char recvbuf[64];
                int clientfdslength = clientfds.size();
                for (int i = 0; i < clientfdslength; ++i)
                {
                    if (clientfds[i] != INVALID_FD && FD_ISSET(clientfds[i], &readset))
                    {
                        memset(recvbuf, 0, sizeof(recvbuf));
                        // 非侦听socket，则接收数据
                        int length = recv(clientfds[i], recvbuf, 64, 0);
                        if (length <= 0)
                        {
                            // 收取数据出错了
                            std::cout << "recv data error, clientfd: " << clientfds[i] << std::endl;
                            close(clientfds[i]);
                            // 不直接删除该元素，将该位置的元素置位INVALID_FD
                            clientfds[i] = INVALID_FD;
                            continue;
                        }

                        std::cout << "clientfd: " << clientfds[i] << ", recv data: " << recvbuf << std::endl;
                    }
                }
            }
        }
    }

    // 6.关闭所有客户端socket
    int clientfdslength = clientfds.size();
    for (int i = 0; i < clientfdslength; ++i)
    {
        if (clientfds[i] != INVALID_FD)
        {
            close(clientfds[i]);
        }
    }

    // 7.关闭侦听socket
    close(listenfd);

    return 0;
}
