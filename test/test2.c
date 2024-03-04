#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include <error.h>

#define SIZE 50

void sigHandler(int sig)
{
    if (sig == SIGINT)
    {
        printf("捕捉到ctril+c,程序退出\n");
        exit(0);
    }   
}

int main()
{
    /* 自定义信号 */
    signal(SIGINT, sigHandler);
    while (1)
    {
        printf("hello\n");
        sleep(2);
    }
    exit(-1);
}

