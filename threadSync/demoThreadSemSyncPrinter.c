#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <string.h>
#include <pthread.h>
#include <error.h>
#include <semaphore.h>

/* 信号量和互斥锁有什么区别:资源 */
/* 互斥锁和读写锁和自旋锁有什么区别：使用场景 */
sem_t g_sem;


/* 全局变量锁*/
pthread_mutex_t g_mutex;

void printer(char * ptr)
{
    /* P操作 */
    sem_wait(&g_sem);
    //pthread_mutex_lock(&g_mutex);
    while (*ptr != '\0')
    {
        putchar(*ptr);
        fflush(stdout);
        ptr++;
        usleep(100);
    }
    /* V操作 */
    sem_post(&g_sem);
    //pthread_mutex_unlock(&g_mutex);
    printf("\n");
}
/* 线程一 */
void * thread_func1(void * arg)
{
    char *ptr = "hello";
    printer(ptr);
    //pthread_exit(NULL);
}
/* 线程二 */
void * thread_func2(void * arg)
{
    char *ptr = "world";
    printer(ptr);
    //pthread_exit(NULL);
}

int main()
{
    /* 初始化信号量 */
    sem_init(&g_sem, 0, NULL);
    /* 最先初始化锁，属性2设置成默认属性 */
    //pthread_mutex_init(&g_mutex, NULL);
    pthread_t tid1;
    pthread_t tid2;

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
    
    //pthread_mutex_lock(&g_mutex);

    /* 释放锁资源：必须解锁之后才可以操作此函数 */
    #if 0
    int ret = pthread_mutex_destroy(&g_mutex);
    if (ret == EBUSY)
    {
        printf("pthread_mutex_destroy error");
        _exit(-1);
    }
    #endif
    
    ？？释放
    return 0;
}