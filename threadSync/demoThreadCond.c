#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <string.h>
#include <pthread.h>
#include <stdlib.h>

/* 优化：不能一直生产 && */
#define MAX_SIZE 10

/* 锁资源 */
pthread_mutex_t g_mutex;
/* 条件变量 */
pthread_cond_t g_notEmpty;/* 生产者给消费者 */
pthread_cond_t g_notFull;/* 消费者给生产者发 */

/* 生产容量 */
int g_size = 0;

/* 链表结点 */
typedef struct Node
{
    int val;
    struct Node * next;
}Node;
/* 定义一个头指针 */
Node * head = NULL;


/* 生产者消费者模型 */
void * produceFunc(void * arg)
{
    //pthread_detach(pthread_self()); 系统回收
    int count = 1;
    while (1)
    {

        Node * newNode = (Node *) malloc(sizeof(Node) * 1);
        if (newNode == NULL)
        {
            perror("malloc error");
            pthread_exit(NULL);
        }
        memset(newNode, 0, sizeof(Node) * 1);
        /* 赋值 */
        newNode->val = count++;
        
        /* 加锁 */
        pthread_mutex_lock(&g_mutex);
        /* 每生产一个就要加1 */
        if (g_size > MAX_SIZE)
        {
            pthread_cond_wait(&g_notFull, &g_mutex);
        }
        
        /* 头插入 */
        newNode->next = head;
        head = newNode;

        printf("=====produce:%ld\t%d\n", pthread_self(), newNode->val);
        pthread_mutex_unlock(&g_mutex);

        /* 信号通知 */
        pthread_cond_signal(&g_notEmpty);
        /* 休眠 */
        sleep(rand() % 3);
    }
    /* 线程退出 */
    pthread_exit(NULL);
}

void * consumeFunc(void * arg)
{
    while (1)
    {
        /* 等待条件变量 */
        pthread_mutex_lock(&g_mutex);
        /* 如果没有东西的话就等待，如果有东西直接去拿 */
        /* 多消费者会有竞争 用while，一直去查看有没有东西 */
        while (head == NULL)
        {
            /* 等待信号，接收信号并解锁 */
            pthread_cond_wait(&g_notEmpty, &g_mutex);
        }
        
        /* 程序进来就证明有数据，开始拿 */
        Node * delNode = head;
        head = head->next;

        printf("consume:%ld\t %d\n",pthread_self(), delNode->val);
        /* 拿完需要释放内存 */
        if (delNode)
        {
            free(delNode);
            delNode = NULL;
        }
        /* 每拿走一个就要减一 */

        /* 操作完解锁 */
        pthread_mutex_unlock(&g_mutex);
       
    }
    
}

int main()
{
    /* 初始化锁和条件变量 */
    pthread_mutex_init(&g_mutex, NULL);
    pthread_cond_init(&g_notEmpty, NULL);
    pthread_cond_init(& g_notFull, NULL);
    /* 生产者进程 */
    pthread_t produce_tid;
    /* 消费者进程 */
    pthread_t consume_tid;

    /* 生产者 */
    int ret = pthread_create(&produce_tid, NULL, produceFunc, NULL);
    if (ret != 0)
    {
        printf("pthread_creat error\n");
        _exit(-1);
    }
    
    /* 消费者 */
    ret = pthread_create(&consume_tid, NULL, consumeFunc, NULL);
    if (ret != 0)
    {
        printf("pthread_creat error\n");
        _exit(-1);
    }
    /* 主线程回收 */
    pthread_join(produce_tid, NULL);
    pthread_join(consume_tid, NULL);

    /* 释放锁资源和条件变量资源 */
    pthread_mutex_destroy(&g_mutex);
    pthread_cond_destroy(&g_notEmpty);
    pthread_cond_destroy(& g_notFull);


    return 0;
}