#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/epoll.h>
int main(int argc, char *argv[])
{
    int fd[2];
    pipe(fd);
    // 创建子进程
    pid_t pid;
    pid = fork();
    if (pid < 0)
        perror("");
    else if (pid == 0) // 子进程
    {
        close(fd[0]);
        char buf[5];
        char ch = 'a';
        while (1)
        {
            sleep(3);
            memset(buf, ch++, sizeof(buf));
            write(fd[1], buf, 5);
        }
    }
    else // 父进程
    {
        close(fd[1]);
        // 创建树
        int epfd = epoll_create(1); // 创建树根
        struct epoll_event ev, evs[1];
        ev.data.fd = fd[0];
        ev.events = EPOLLIN;
        epoll_ctl(epfd, EPOLL_CTL_ADD, fd[0], &ev); // 上树
        // 监听
        while (1)
        {
            int n = epoll_wait(epfd, evs, 1, -1); // 监听
            if (n == 1)
            {
                char buf[128] = "";
                int ret = read(fd[0], buf, sizeof(buf));
                if (ret <= 0) // 管道关闭
                {
                    close(fd[0]);
                    epoll_ctl(epfd, EPOLL_CTL_DEL, fd[0], &ev); // 下树
                    break;
                }
                else
                {
                    printf("%s\n", buf);
                }
            }
        }
    }

    return 0;
}