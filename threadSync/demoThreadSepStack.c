#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <string.h>
#include <pthread.h>

pthread_mutex_t g_mutex = PTHREAD_MUTEX_INITIALIZER;

/*余量 */
int g_margin = 10;

/* 线独享栈空间 */
void * thread_func1(void * arg)
{
    //usleep(50);
    while (1)
    {
        /* 加锁 */
        pthread_mutex_lock(&g_mutex);
        if (g_margin > 0)
        {
        /* 休眠的时候，会将CPU资源让出去 */
            usleep(100);
            g_margin -= 1;
        }
        /* 拿到东西就解锁 */
        pthread_mutex_unlock(&g_mutex);
        printf("thread1 num:%d\n", g_margin);
        if (g_margin <= 0)
        {
            break;
        }
    }

    printf("thread1 num:%d\n", g_margin);
    pthread_exit(NULL);
}

void * thread_func2(void * arg)
{
    usleep(50);
    while (1)
    {
        pthread_mutex_lock(&g_mutex);
        if (g_margin >= 2)
        {
            usleep(20000);
            g_margin -= 2;
        }
        pthread_mutex_unlock(&g_mutex);
        printf("thread2 num:%d\n", g_margin);
        if (g_margin <= 0)
        {
            break;
        }
        
    }
    
    printf("thread2 num:%d\n", g_margin);
    pthread_exit(NULL);
}

int main()
{
    
    pthread_t tid1;
    pthread_t tid2;
    /* 创建两个进程 */
    int ret = pthread_create(&tid1, NULL, thread_func1, NULL);
    if (ret != 0)
    {
        printf("pthread_creat error\n");
        _exit(-1);
    }
    
    ret = pthread_create(&tid2, NULL, thread_func2, NULL);
    if (ret != 0)
    {
        printf("pthread_creat error\n");
        _exit(-1);
    }

    /* 主线程回收子线程的资源 */
    pthread_join(tid1, NULL);
    pthread_join(tid2, NULL);
    /* 释放资源 */
    pthread_attr_destroy();
    
    return 0;
}