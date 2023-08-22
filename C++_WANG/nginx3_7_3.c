#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/stat.h>
#include <fcntl.h>

//创建守护进程
int ngx_daemon()
{
    int fd;

    switch(fork())
    {
        case -1:
            printf("fork()失败\n");
            return -1;
        case 0:
            // 子进程
            break;
        default:
            // 父进程
            exit(0);
    }

    //只有子进程才能执行到这里
    if (setsid() == -1) //创建新会话
    {
        printf("setsid()失败\n");
        return -1;
    }
    umask(0); //重设文件权限掩码
    fd = open("/dev/null", O_RDWR); //打开黑洞设备
    if (fd == -1)
    {
        printf("open(\"/dev/null\")失败\n");
        return -1;
    }

    if (dup2(fd, STDIN_FILENO) == -1) //重定向标准输入到黑洞
    {
        printf("dup2(STDIN)失败\n");
        return -1;
    }
    if (dup2(fd, STDOUT_FILENO) == -1) //重定向标准输出到黑洞
    {
        printf("dup2(STDOUT)失败\n");
        return -1;
    }
    if (fd > STDERR_FILENO) //重定向标准错误到黑洞
    {
        if (close(fd) == -1)
        {
            printf("close()失败\n");
            return -1;
        }
    }
    return 1;
}

int main()
{
    if (ngx_daemon() != 1)
    {
        //创建守护进程失败
        return 1;
    }
    else
    {
        //创建守护进程成功
        for (;;)
        {
            sleep(1);
            printf("休息1s\n"); //这个printf是为了测试守护进程是否正常工作（打印不出任何结果）
        }
    }

    return 0;
}