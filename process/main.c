#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>

int main()
{
    /* 或许进程号 */
    pid_t currentPid = getpid();
    pid_t parentPid = getppid();

    printf("currentPid:%d\n", currentPid);
    printf("parentPid:%d\n", parentPid);

    /* 进程的创建 */
    
    return 0;
}