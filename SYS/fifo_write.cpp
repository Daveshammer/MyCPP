#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#define P_FIFO "./p_fifo"

/*
    有名管道fifo，用于非亲缘关系的进程间通信
    提供了一个路径名与管道关联，以文件的形式存在于文件系统中
    
    对现有管道写入数据
*/

int main(int argc, char **argv){
    int fd;
    if(argc< 2){
        printf("please input the write data.\n");
    }
    fd = open(P_FIFO, O_WRONLY|O_NONBLOCK); /*非阻塞方式*/
    if(fd == -1) {
        printf("open failed!\n");
        return 0;
    }else{
        printf("open success!");
    }
    // write(fd, argv[1], 100); /*将argv[1]写道fd里面去*/
    write(fd, "abc", 100); /*将"abc"写道fd里面去*/
    close(fd);
    return 0;
}