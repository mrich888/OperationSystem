#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <string.h>

typedef struct StuInfo
{
    int age;
    char sex;
}StuInfo;


/* 线程1 */
void * thread_func1(void * arg)
{ 
    /* 线程分离:主线程休眠时，该线程还可以继续输出，等到结束后系统自动回收 */
    pthread_detach(pthread_self());

    StuInfo * info = (StuInfo *)arg;
    printf("age:%d\tsex:%c\n", info->age, info->sex);
    sleep(3);

    printf("age:%d\tsex:%c\n", info->age, info->sex);
    pthread_exit(NULL);
}

int main()
{
    pthread_t tid1;

    StuInfo stu;
    stu.age = 10;
    stu.sex = 'f';
    //int num = 100;
    /* 创建线程 */
    int ret = pthread_create(&tid1 , NULL, thread_func1, (void *)&stu);//线程标识符；   
    if (ret != 0)
    {
        strerror(ret);
        _exit(-1);
    }
    //sleep(100);
    sleep(1);
    return 0;
}