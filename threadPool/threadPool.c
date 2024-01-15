#include "threadPool.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DEFAULT_MIN_THREADS 5
#define DEFAULT_MAX_THREADS 10
#define DEFAULT_QUEUE_CAPACITY 100

enum STATUS_CODE
{
    ON_SUCCESS,
    NULL_PTR,
    MALLOC_ERROR,
    ACCESS_INVAILD,
    UNKONW_ERROR,
};

void * threadHander(void * arg)
{
    pthread_exit(NULL);
}

/* 线程池初始化 */
int threadPoolInit(threadpool_t *pool, int minThreads, int maxThreads, int queueCapacity)
{
    /* 判断是否为空 */
    if (pool == NULL)
    {
        return NULL_PTR;
    }
    do
    {
        /* 判断是否合法 */
        if (minThreads < 0 || maxThreads > 0 || minThreads > maxThreads)
        {
            /* code */
            minThreads = DEFAULT_MIN_THREADS;
            maxThreads = DEFAULT_MAX_THREADS;
        }

        /* 初始化,更新线程池属性 */
        pool->minThreads = minThreads;
        pool->maxThreads = maxThreads;

        /* 判断容量是否合法 */
        if (queueCapacity < 0)
        {
            queueCapacity = DEFAULT_QUEUE_CAPACITY;
        }

        /* 初始化,更新线程池属性 */
        {
            pool->queueCapacity = queueCapacity;
            pool->taskQueue = (task_t *)malloc(sizeof(task_t) * pool->queueCapacity);
            if (pool->taskQueue)
            {
                perror("malloc error");
                break;
            }
            memset(pool->taskQueue, 0, sizeof(task_t) * pool->queueCapacity);
            pool->queueFront = 0;
            pool->queueRear = 0;
            pool->queueSize = 0;
        }

        /* ⭐ 为线程ID分配堆空间 */
        pool->threadIds = (threadpool_t *)malloc(sizeof(threadpool_t ) * maxThreads);// pool->maxThreads = maxThreads 两个都行
        if (pool->threadIds == NULL)
        {
            perror("malloc error");
            exit(-1);
        }

        /* 清楚脏数据 */
        memset(pool->threadIds, 0, sizeof(threadpool_t ) * maxThreads);
        /* ⭐ 创建线程 空间分配最大的，线程创建最小的 */
        int ret = 0;
        for (int idx = 0; idx < pool->minThreads; idx++)
        {
            if (pool->threadIds[idx] == 0)
            {
                 ret = pthread_create(&(pool->threadIds[idx]), NULL, threadHander, NULL);
                if (ret != 0)
                {
                    perror("thread create error");
                    break;
                }
            }    
        }

        /* 此ret是创建线程的返回值 未创建成功 */
        if (ret != 0)
        {
            break;
        }

        return ON_SUCCESS;

    } while (0);

    /* 回收堆空间 */
    if (pool->taskQueue != NULL) 
    {
        free(pool->taskQueue);
        pool->taskQueue = NULL;
    }
    
    /* 程序执行到这里一定遇到了问题 */
    for (int idx = 0; idx < pool->minThreads; idx++)
    {
        if (pool->threadIds[idx] != 0)
        {
            pthread_join(pool->threadIds[idx], NULL);
        }
        
    }
    /* 释放资源 */
    if (pool->threadIds != NULL)
    {
        free(pool->threadIds);
    }

    return UNKONW_ERROR;     
    
}

/* 线程池的销毁 */
int threadOPoolDestroy(threadpool_t *pool)
{

}