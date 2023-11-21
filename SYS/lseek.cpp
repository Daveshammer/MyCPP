#include <iostream>
#include <fcntl.h>
#include <unistd.h>
int main() {
    // 没有则创建这个文件
    int fd = open("aa.txt", O_CREAT | O_RDWR);

    // 获取文件大小
    int file_size = lseek(fd, 0, SEEK_END);
    printf("file size = %d\n", file_size);

    // 拓展文件大小 2000字节
    int total_size = lseek(fd, 2000, SEEK_END);
    printf("total size = %d\n", total_size);

    // 写入数据
    write(fd, "a", 1);

    return 0;
}