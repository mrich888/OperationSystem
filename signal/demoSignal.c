#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include <error.h>

#define SIZE 50

/* 捕捉信号 */
void sigHandler(int sig)
{
    printf("sig:%d\n", sig);

    /* 只是提醒 */
    printf("heiheihei\n");
}

int main()
{
    /* 注册信号 */
    /* 1.默认动作 */
    // signal(SIGINT, SIG_DFL);

    // /* 2.忽略 SIG_IGN */
    // signal(SIGINT, SIG_IGN);

    /* 3.自定义 */
    signal(SIGINT, sigHandler);

    while (1)
    {
        printf("hello world\n");
        sleep(2);
    }
    
   
    return 0;
}