#include <iostream>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <sys/wait.h>

//参考Stanford CS110
 int main() {
    char* command = "-l";
    pid_t pid = fork();
    if (pid == 0) {
        char *arguments[] = {"/usr/bin/ls", "-a", (char *) command, NULL};
        execvp(arguments[0], arguments);
        printf("Failed to invoke /bin/sh to execute the supplied command.");
        exit(0);
    }
    // 父进程
    int status;
    waitpid(pid, &status, 0);
    // 没有学习过如何根据进程退出状态，判断信息
    return WIFEXITED(status) ? WEXITSTATUS(status) : -WTERMSIG(status);
}