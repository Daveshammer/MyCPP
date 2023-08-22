#include <unistd.h>
#include <stdio.h>
#include <arpa/inet.h>
#include <sys/socket.h>

int main()
{
    // 创建套接字
    int sock_fd;
    sock_fd = socket(AF_INET, SOCK_STREAM, 0);

    // 连接服务器
    struct sockaddr_in server_addr;
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(8080);
    inet_pton(AF_INET, "10.0.1.235", &server_addr.sin_addr.s_addr);
    connect(sock_fd, (struct sockaddr*)&server_addr, sizeof(server_addr));

    // 读写数据
    char buf[1024];
    while (1)
    {
        int n = read(STDIN_FILENO, buf, sizeof(buf)); // 从标准输入读取数据
        write(sock_fd, buf, n); // 发送给服务器

        n = read(sock_fd, buf, sizeof(buf)); // 从服务器接收数据
        write(STDOUT_FILENO, buf, n); // 输出到屏幕
    }

    // 关闭套接字
    close(sock_fd);

    return 0;
}