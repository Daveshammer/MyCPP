// 进阶版select，通过数组防止遍历1024个文件描述符
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <arpa/inet.h>
#include <ctype.h>
#include <sys/select.h>

#include "wrap.h"

#define SERV_PORT 8888

/**
 * gcc 06select.c  wrap.c
 * nc 127.0.0.1 8888
*/

int main()
{
    int i, j, n, maxi;

    int nready, client[FD_SETSIZE]; // 自定义数组client，防止遍历1024个文件描述符
    int maxfd, listenfd, connfd, sockfd;
    char buf[BUFSIZ], str[INET_ADDRSTRLEN];
    struct sockaddr_in clie_addr, serv_addr;
    socklen_t clie_addr_len;
    fd_set rset, allset; // rset 读事件文件描述符集合 allset用来暂存

    // 创建监听套接字
    listenfd = Socket(AF_INET, SOCK_STREAM, 0);
    // 端口复用
    int opt = 1;
    setsockopt(listenfd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));

    bzero(&serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    serv_addr.sin_port = htons(SERV_PORT);

    // 绑定
    Bind(listenfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr));

    // 监听
    Listen(listenfd, 128);

    maxfd = listenfd; // 起初

    maxi = -1; // client[]数组的下标
    for (int i = 0; i < FD_SETSIZE; i++)
    {
        client[i] = -1; // 初始化为-1
    }

    FD_ZERO(&allset);          // 清空
    FD_SET(listenfd, &allset); // 将监听套接字添加到allset中

    while (1)
    {
        rset = allset;

        nready = select(maxfd + 1, &rset, NULL, NULL, NULL);
        if (nready < 0)
        {
            perr_exit("select error");
        }
        if (FD_ISSET(listenfd, &rset)) // 有新的连接到来
        {
            clie_addr_len = sizeof(clie_addr);
            // 提取新的连接
            connfd = Accept(listenfd, (struct sockaddr *)&clie_addr, &clie_addr_len);
            printf("received from IP=%s at PORT=%d\n",
                   inet_ntop(AF_INET, &clie_addr.sin_addr.s_addr, str, sizeof(str)),
                   ntohs(clie_addr.sin_port));

            // 找到client[]中的空闲位置
            for (i = 0; i < FD_SETSIZE; i++)
            {
                if (client[i] < 0)
                {
                    client[i] = connfd;
                    break;
                }
            }
            if (i == FD_SETSIZE)
            {
                fputs("too many clients\n", stderr);
                exit(1);
            }

            FD_SET(connfd, &allset); // 将新的连接添加到allset中
            if (connfd > maxfd)
            {
                maxfd = connfd;
            }
            if (i > maxi)
            {
                maxi = i; // 保证maxi存的总是client[]最后一个元素下标
            }

            if (--nready == 0)
            {
                continue;
            }
        }

        for (int i = 0; i <= maxi; i++) /// 检测哪个clients 有数据就绪
        {
            if ((sockfd = client[i]) < 0)
            {
                continue;
            }
            if (FD_ISSET(sockfd, &rset))
            {
                if ((n = Read(sockfd, buf, sizeof(buf))) == 0) // client关闭链接时，服务器端也关闭对应链接
                {
                    Close(sockfd);
                    FD_CLR(sockfd, &allset);
                    client[i] = -1;
                }
                else if (n > 0)
                {
                    for (j = 0; j < n; j ++) // 小写转大写
                    {
                        buf[j] = toupper(buf[j]);
                    }
                    Write(sockfd, buf, n); // 回写给客户端
                    Write(STDOUT_FILENO, buf, n);
                }
                if (--nready == 0) // 最后一个已经处理完毕
                {
                    break;
                }
            }
        }
    }

    // 关闭监听套接字
    Close(listenfd);

    return 0;
}