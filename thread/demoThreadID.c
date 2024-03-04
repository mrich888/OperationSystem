#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

int main()
{
    /* 获取线程id */
    pthread_t tid =  pthread_self();
    printf("tid :%ld\n", tid);

    pid_t pid = getpid();
    printf("pid:%d\n", pid);
    
    return 0;
}