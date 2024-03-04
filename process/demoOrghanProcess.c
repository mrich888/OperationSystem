#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <error.h>
#include <wait.h>

int main()
{
    int num = 100;
    /* 创建一个子进程 */
    pid_t pid = fork();
    /* 本身就是一个子进程和一个父进程，并且进程间相互独立，理论上哪个进程先执行不知道 */
    if (pid < 0)
    {
        /* 失败 */
        perror("fork error");
        return 0;
    }
    
    if (pid == 0)
    {
        /* 子进程 */
        pid_t childPid = getpid();
        printf("childPid:%d\n", childPid);    
        /* 子进程休眠 */
        sleep(3);    
    }
    else if (pid > 0)
    {
        /* 父进程 */
        pid_t parentPid = getppid();
        printf("parentPid process:%d\n", parentPid); 
 
    }
    //wait(NULL);

    //printf("hello world!\n");
}