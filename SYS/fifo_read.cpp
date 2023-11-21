#include <stdio.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#define P_FIFO "./p_fifo"

/*
    有名管道fifo，用于非亲缘关系的进程间通信
    提供了一个路径名与管道关联，以文件的形式存在于文件系统中

    创建管道，等待读入数据
*/

int main(int argc, char** argv){
    char cache[100];
    int fd;
    memset(cache,0, sizeof(cache));   /*初始化内存*/
    if(access(P_FIFO,F_OK)==0){  /*管道文件存在*/
        execlp("rm","-f", P_FIFO, NULL);  /*删掉*/
        printf("access.\n");
    }
    if(mkfifo(P_FIFO, 0777) < 0){ // 参数：管道文件名，权限
        printf("createnamed pipe failed.\n");
    }
    fd = open(P_FIFO, O_RDONLY|O_NONBLOCK); /*非阻塞方式打开，只读*/
    while(1){
        memset(cache,0, sizeof(cache));
        if((read(fd,cache, 100)) == 0 ){ /*没有读到数据*/
            printf("nodata:\n");
        }
        else{
            printf("getdata:%s\n", cache); /*读到数据，将其打印*/
        }
        sleep(1);/*休眠1s*/
    }
    close(fd);
    return 0;
}