#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <stdlib.h>

int main()
{
    // 创建套接字
    int fd = socket(AF_INET, SOCK_DGRAM, 0); // SOCK_DGRAM: UDP
    // 绑定
    struct sockaddr_in myaddr;
    myaddr.sin_family = AF_INET;
    myaddr.sin_port = htons(9000);
    inet_pton(AF_INET, "127.0.0.1", &myaddr.sin_addr.s_addr);
    int ret = bind(fd, (struct sockaddr*)&myaddr, sizeof(myaddr));
    if (ret < 0)
    {
        perror("");
        exit(0);
    }
    // 读写
    char buf[1500] = "";

    struct sockaddr_in servaddr; // 服务器socket地址
    int len = sizeof(servaddr);
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(8888); // 服务器端口
    inet_pton(AF_INET, "127.0.0.1", &servaddr.sin_addr.s_addr);

    int n = 0;
    while (1)
    {
        n = read(STDIN_FILENO, buf, sizeof(buf));
        sendto(fd, buf, n, 0, (struct sockaddr*)&servaddr, len); // 发送给服务器
        memset(buf, 0, sizeof(buf));
        n = recvfrom(fd, buf, sizeof(buf), 0, (struct sockaddr*)&servaddr, &len); // 从客户端接收数据，并将客户端地址保存到servaddr中
        // n = recvfrom(fd, buf, sizeof(buf), 0, NULL, NULL); // 因为已经知道ip了，所以不需要再传入地址
        if (n < 0)
        {
            perror("");
            exit(0);
        }
        else
        {
            printf("%s\n", buf);
        }
    }

    // 关闭
    close(fd);

    return 0;
}