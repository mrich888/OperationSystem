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
    StuInfo * info = (StuInfo *)arg;
    printf("age:%d\tsex:%c\n", info->age, info->sex);
  
    sleep(1);
    pthread_exit(NULL);
}

/* 线程2 */
void * thread_func2(void * arg)
{ 
    int val = *(int *)arg;
    printf("val:%d\n", val);
    sleep(1);
    pthread_exit(NULL);
}


int main()
{
    pthread_t tid1;
    pthread_t tid2;
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
    ret = pthread_create(&tid2 , NULL, thread_func2, (void *)&stu);//线程标识符；   
    if (ret != 0)
    {
        strerror(ret);
        _exit(-1);
    }


    ret = pthread_join(tid1, NULL);
    if (ret != 0)
    {
        printf("pthread_join error");
    }

    ret = pthread_join(tid2, NULL);
    if (ret != 0)
    {
        printf("pthread_join error");
    }
    
    printf("hello world\n");
    //sleep(3);//以秒为单位暂停

    return 0;
}