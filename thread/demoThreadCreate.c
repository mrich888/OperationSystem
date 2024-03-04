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

int g_retVal = 100;
void * thread_func(void * arg)
{ 
    /* 拿数据需要定义一个变量承接它，并且进行强转 */
    //int val = *(int *)arg;
    //printf("val:%d\n", val);

    StuInfo * info = (StuInfo *)arg;
    printf("age:%d\nsex:%c\n", info->age, info->sex);
    
    printf("I am a new thread\n");
    pthread_t tid = pthread_self();
    printf("tid :%ld\n", tid);
    /* 线程阻塞 */
    //sleep(300);
    sleep(3);

    /* 栈空间:离开函数。栈空间的地址就被释放了 */
    // 所以不能在这里定义 int retVal = 100;
    pthread_exit((void *)&g_retVal);
}


int main()
{
    pthread_t tid;
    StuInfo stu;
    stu.age = 10;
    stu.sex = 'f';
    //int num = 100;
    /* 创建线程 */
    int ret = pthread_create(&tid , NULL, thread_func, (void *)&stu);//线程标识符；   
    if (ret != 0)
    {
        strerror(ret);
        _exit(-1);
    }
    /* 证明回调函数里的进程号是否和创建的tid相同，相同的话线程回收时就可以传入main中的tid */
    printf("maintid :%ld\n", tid);

    /*  */
    int *retVal = NULL;
    /* 等待进程tid线程结束后才输出。相当于wait */
    pthread_join(tid, (void **)&retVal);
    printf("retVal:%d\n", *retVal);

    printf("hello world\n");
    sleep(3);//以秒为单位暂停

    #if 0
    usleep(0.3);//以微妙为单位暂停
    while(1);
    #endif
    return 0;
}