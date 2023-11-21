#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/fcntl.h>

/*
 匿名非阻塞管道，用于父子进程通信
*/
int main()
{
    int fd[2]; //0为读 1为写
    pid_t pid;
    int ret = pipe(fd);
    if (ret == -1)
    {
        perror("pipe error!");
        exit(1);
    }
    pid = fork();
    if (pid == -1)
    {
        perror("fork error!");
        exit(1);
    }
    else if (pid == 0)
    {
        //子进程 读
        close(fd[1]);
        //非阻塞管道 没有数据直接返回
        int flags = fcntl(fd[0], F_GETFL);
        flags |= O_NONBLOCK;
        fcntl(fd[0], F_SETFL, flags);

        char buf[1024];
    tryagain:
        ret = read(fd[0], buf, sizeof(buf));
        if (ret == -1)
        {
            if (errno == EAGAIN)
            { //如果数据没到达 会返回EAGAIN
                write(STDOUT_FILENO, "try agian!\n", 11);
                sleep(1);
                goto tryagain;
            }
            else
            {
                perror("read error");
                exit(1);
            }
        }
        write(STDOUT_FILENO, buf, ret);
        close(fd[0]);
    }
    else if (pid > 0)
    {
        //父进程 写
        sleep(5);
        close(fd[0]);
        write(fd[1], "hello pipe\n", 11);
        wait(NULL);
        close(fd[1]);
    }
    return 0;
}
