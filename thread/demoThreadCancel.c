#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <stdio.h>

void thread_Func ( void *arg)
{
     /* 线程分离 */
    pthread_detach(pthread_self());
    
    while (1)
    {
        printf("i am thread_func... ");
        sleep(1);
    }
    printf("hello world");
    pthread_exit(NULL);
}

int main()
{

    pid_t tid;
    int ret = pthread_create(&tid, NULL, thread_Func, NULL);
    if (ret != 0)
    {
        printf("thread create error");
        _exit(-1);
    }

    sleep(3);
    pthread_cancel(tid);
    
    while (1)
    {
        sleep(3);
    }
    
    return 0;
}