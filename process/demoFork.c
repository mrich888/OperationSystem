#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <error.h>

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
        /* 让出cpu,使父进程先执行 */
        sleep(1);
        /* 子进程 */
        pid_t childPid = getpid();
        printf("childPid:%d\n", childPid);    

        // pid_t parentPid = getppid();
        // printf("parentPid:%d\n", parentPid); 

        while (1)
        {
            /* 此时就需要设置休眠，使两个进程和谐的进行 */
            sleep(3);
        }
            
    }
    else if (pid > 0)
    {
        /* 父进程 */
        pid_t parentPid = getppid();
        printf("parentPid process:%d\n", parentPid); 

        while (1)
        {
            /* 此时就需要设置休眠，使两个进程和谐的进行 */
            sleep(3);
        }
          
    }
    /* 之后再做操作的话，父子进程都会做 */
    /* hello world会同时出现在两个进程中 */
    printf("hello world!");
    

    return 0;
}