#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include <error.h>

#define SIZE 50

int main()
{
    for (int idx = 0; idx < SIZE; idx++)
    {
        if (idx == 5)
        {
            /* 给当前进程发送ctrl + c */
            raise(SIGINT);
            /* 等价于：kill(getpid(), SIGNIT);  */
        }
        printf("idx = %d\n", idx);
        sleep(1);
    }

    return 0;
}