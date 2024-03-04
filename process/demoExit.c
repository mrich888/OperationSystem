#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <error.h>
#include <stdlib.h>

int main()
{
    /* 创建进程 */
    pid_t pid = fork();
    if (pid < 0)
    {
        perror("fork error");
    }

    if (pid == 0)
    {
        /* 子进程 */
        pid_t childPid = getpid();
        printf("childPid:%d\n", childPid);

        /* 子进程退出 */
        _exit(0);
    }
    else if (pid > 0)
    {
        /* 父进程 */
        pid_t parentPid = getppid();
        printf("parentPid:%d\n", parentPid);
    }
    /* 子进程已经结束，那么子进程的代码就不会到这边了 */

    printf("hello world !\n");
    

    return 0;
}