#include <stdio.h>
#include <stdlib.h> //malloc,exit
#include <unistd.h> //fork
#include <signal.h>
#include <sys/wait.h> //waitpid

// 信号处理函数
void sig_usr(int signo)
{
    int status;
    switch(signo)
    {
        case SIGUSR1:
            printf("收到了SIGUSR1信号，进程ID = %d\n", getpid());
            break;
        case SIGCHLD:
            printf("收到了SIGCHLD信号，进程ID = %d\n", getpid());
            pid_t pid = waitpid(-1, &status, WNOHANG); //防止子进程杀死后变为僵尸进程
            if (pid == 0) //子进程还没结束
                return;
            if (pid == -1) //有错误也立即返回
                return;
            break;
    }
}

int main()
{
    pid_t pid;
    printf("进程开始执行\n");
    if (signal(SIGCHLD,sig_usr) == SIG_ERR)
    {
        printf("无法捕捉SIGCHLD信号\n");
        exit(1);
    }
    pid = fork();

    if (pid < 0)
    {
        printf("子进程创建失败\n");
        exit(1);
    }

    //以下部分子进程和父进程都会运行
    for (;;)
    {
        sleep(1);
        printf("休息1s，进程ID = %d\n", getpid());
    }
    printf("再见了\n");

    return 0;
}