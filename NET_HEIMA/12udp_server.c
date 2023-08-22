#include <stdio.h>
#include <sys/socket.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <string.h>
#include <stdlib.h>

int main()
{
    // 创建套接字
    int fd = socket(AF_INET, SOCK_DGRAM, 0); // SOCK_DGRAM: UDP
    // 绑定
    struct sockaddr_in myaddr;
    myaddr.sin_family = AF_INET;
    myaddr.sin_port = htons(8888);
    inet_pton(AF_INET, "127.0.0.1", &myaddr.sin_addr.s_addr);
    // myaddr.sin_addr.s_addr = inet_addr("127.0.0.1"); // 只能处理IPv4
    int ret = bind(fd, (struct sockaddr*)&myaddr, sizeof(myaddr));
    if (ret < 0)
    {
        perror("");
        exit(0);
    }
    // 读写
    char buf[1500] = "";
    struct sockaddr_in cliaddr;
    socklen_t len = sizeof(cliaddr);
    while (1)
    {
        bzero(buf, sizeof(buf));
        int n = recvfrom(fd, buf, sizeof(buf), 0, (struct sockaddr*)&cliaddr, &len); // 从客户端接收数据，并将客户端地址保存到cliaddr中
        if (n < 0) 
        {
            perror("");
            break;
        }
        else
        {
            printf("%s\n", buf);
            sendto(fd, buf, n, 0, (struct sockaddr*)&cliaddr, len); // 发送给客户端
        }
    }
    // 关闭
    close(fd);

    return 0;
}