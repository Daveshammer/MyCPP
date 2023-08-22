#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

// 信号处理函数
void sig_quit(int signo)
{
    printf("收到了SIGQUIT信号\n");
}

int main(int argc, char *const *argv)
{
    sigset_t newmask, oldmask, pendmask;
    if (signal(SIGQUIT, sig_quit) == SIG_ERR)
    {
        printf("无法捕捉SIGQUIT信号\n");
        exit(1);
    }

    sigemptyset(&newmask);        // newmask信号集中所有信号清零
    sigaddset(&newmask, SIGQUIT); // 再来SIGQUIT信号时，进程就收不到

    if (sigprocmask(SIG_BLOCK, &newmask, &oldmask) < 0) //将newmask中的信号添加到当前进程屏蔽字中
    {
        printf("sigprocmask(SIG_BLOCK)失败\n");
        exit(1);
    }
    printf("我要开始休息10s了----begin----，此时无法收到SIGQUIT信号\n");
    sleep(10);
    printf("我已经休息了10s----end----\n");

    if (sigismember(&newmask, SIGQUIT))
    {
        printf("SIGQUIT信号被屏蔽了\n");
    }
    else
    {
        printf("SIGQUIT信号没有被屏蔽\n");
    }
    if (sigismember(&newmask, SIGHUP)) // 测试另一个信号
    {
        printf("SIGHUP信号被屏蔽了\n");
    }
    else
    {
        printf("SIGHUP信号没有被屏蔽\n");
    }

    // 取消对SIGQUIT的屏蔽（阻塞），把信号集还原回去
    if (sigprocmask(SIG_SETMASK, &oldmask, NULL) < 0) //将oldmask的值设置为新的进程屏蔽字
    {
        printf("sigprocmask(SIG_SETMASK)失败\n");
        exit(1);
    }
    printf("sigprocmask(SIG_SETMASK)成功\n");

    if (sigismember(&oldmask, SIGQUIT)) // 测试SIGQUIT是否被置位
    {
        printf("SIGQUIT信号被屏蔽了\n");
    }
    else
    {
        printf("SIGQUIT信号没有被屏蔽，可以发送SIGQUIT信号，我要sleep(10)s\n");
        int mysl = sleep(10);
        if (mysl > 0)
        {
            printf("sleep还没睡够，剩余%ds\n", mysl);
        }
    }
    printf("再见了\n");

    return 0;
}