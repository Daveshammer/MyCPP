#include <stdio.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <unistd.h>
#include <string.h>

int main()
{
    // 创建套接字
    int lfd = socket(AF_INET, SOCK_STREAM, 0);
    // 绑定
    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_port = htons(8080);
    // addr.sin_addr.s_addr = INADDR_ANY;  
    inet_pton(AF_INET, "127.0.0.1", &addr.sin_addr.s_addr);
    int ret = bind(lfd, (struct sockaddr*)&addr, sizeof(addr));
    if (ret < 0)
    {
        perror("");
        // exit(0);
    }
    // 监听
    listen(lfd, 128);
    // 提取
    struct sockaddr_in cliaddr;
    socklen_t len = sizeof(cliaddr);
    int cfd = accept(lfd, (struct sockaddr*)&cliaddr, &len);
    char ip[16] = "";
    printf("new client ip=%s port%d\n", inet_ntop(AF_INET, &cliaddr.sin_addr.s_addr, ip, 16),
        ntohs(cliaddr.sin_port));
    // 读写
    char buf[1024];
    while (1)
    {
        // bzero(buf, sizeof(buf));
        memset(buf, 0, sizeof(buf));
        int n = 0;
        n = read(cfd, buf, sizeof(buf));
        if (n == 0) // 客户端关闭
        {
            printf("client close");
            break;
        }
        printf("%s\n", buf);
    }
    // 关闭
    close(lfd);
    close(cfd);

    return 0;
}