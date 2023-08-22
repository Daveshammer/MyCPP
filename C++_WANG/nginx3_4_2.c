#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

// 信号处理函数
void sig_usr(int signo)
{
    int *p;
    p = (int *)malloc(sizeof(int));
    free(p);
    // printf("sig_usr:malloc和free");

    if (signo == SIGUSR1)
    {
        printf("收到了SIGUSR1信号\n");
    }
    else if (signo == SIGUSR2)
    {
        printf("收到了SIGUSR2信号\n");
    }
    else
    {
        printf("收到了未捕捉的信号信号\n");
    }
}

int main()
{
    if (signal(SIGUSR1, sig_usr) == SIG_ERR)
    {
        printf("无法捕捉SIGUSR1信号\n");
    }
    if (signal(SIGUSR2, sig_usr) == SIG_ERR)
    {
        printf("无法捕捉SIGUSR2信号\n");
    }
    for (;;)
    {
        int *p;
        p = (int *)malloc(sizeof(int));
        free(p);
        // printf("main:malloc和free");
    }
    printf("再见\n");

    return 0;
}