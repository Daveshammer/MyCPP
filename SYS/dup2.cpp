#include <iostream>
#include <fcntl.h>
#include <unistd.h>

int main() {
    int fd = open("pp.txt", O_CREAT | O_RDWR, 0744);
    if(fd == -1) {
        printf("open failed!\n");
        exit(1);
    }
    dup2(fd, STDOUT_FILENO); // 原来访问STDOUT_FILENO的，现在变成了访问fd
    // 操作标准输出
    write(STDOUT_FILENO, "bai ge", 6);
    return 0;
}