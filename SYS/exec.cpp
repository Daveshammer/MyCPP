#include <iostream>
#include <unistd.h>

/*
    在某一个进程中运行另一个可执行文件
*/

int main(){
    printf("start...\n");
    execlp("ls", "-a", "-l",NULL);
    printf("never run except wrong\n"); // 这句话不会执行，因为已经执行了另一个可执行文件
}