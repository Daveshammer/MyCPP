#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
/*
ssize_t read(int fd, void*buf, size_t count)
参数说明：
    fd: 是文件描述符, 从command line获取数据时，为0
    buf: 为读出数据的缓冲区；
    count: 为每次读取的字节数（是请求读取的字节数，读上来的数据保存在缓冲区buf中，同时文件的当前读写位置向后移）


ssize_t write(int fd, const void*buf, size_t count);
参数说明：
    fd: 是文件描述符（输出到command line，就是1）
    buf: 通常是一个字符串，需要写入的字符串
    count：是每次写入的字节数
*/

int main()
{
    int fd = open("mytest.txt", O_RDONLY);
    int fx = open("newmytest.txt", O_CREAT | O_WRONLY, 0644);
    char buf[1024];
    int n;
    while (n = read(fd, buf, sizeof(buf)))
    {
        int ret = write(fx, buf, n);
        if (ret == -1)
        {
            perror("write error");
            exit(1);
        }
        printf("write bytes: %d\n", n);
    }

    close(fd);
    close(fx);
    return 0;
}