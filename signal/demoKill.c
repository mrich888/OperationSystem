#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include <error.h>

#define SIZE 5

int main()
{
    /* 创建进程 */
    pid_t pid = fork();
    if (pid == 1)
    {
        perror("");
        _exit(-1);
    }
    else if (pid == 0)
    {
        /* 子进程 */
        printf("child id:%d\n", getpid());
        int idx =0;
        for (int idx = 0; idx < SIZE; idx++)
        {
            printf("i anm son process\n");
        }
        
    }
    else
    {
        /* 子进程的id */
        printf("pid:%d\n", pid);
        /* 父进程 */
        printf("i am parent process\n");
        sleep(2);
        printf("kill sub process now\n");
        kill(pid, SIGINT);
    }
    while (1)
    {
        sleep(3);
    }
    

    return 0;
}