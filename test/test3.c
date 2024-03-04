#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <string.h>

void * handle_func(void *arg)
{
    pthread_detach(pthread_self());
    int num = *(int *)arg;
    printf("num:%d\n", num);
    sleep(3);
    pthread_exit(NULL);
}

int main()
{
    int num = 100;
    /* 创建线程 */
    pthread_t tid;
    int ret = pthread_create(&tid, NULL, handle_func, (void *)&num);
    if (ret != 0)
    {
        perror("create error");
        _exit(-1);
    }
    sleep(1);

    return 0;
}