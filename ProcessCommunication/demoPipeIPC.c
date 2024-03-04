#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <error.h>
#include <wait.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>

#define PIPE_SIZE 2

int main()
{
    /* 创建一个管道数组 */
    int pipefd[PIPE_SIZE];
    memset(pipefd, 0, sizeof(int) * PIPE_SIZE);
    
    /* 创建管道：fd[0]读端 fd[1]写端 */
    pipe(pipefd);

    pid_t pid = fork();
    if (pid < 0)
    {
        perror("fork error");
        _exit(-1);
    }
    if (pid == 0)
    {
        /* 半双工，规定子进程写的话，将读端关掉 */
        close(pipefd[0]);
        /* 子进程写 */
        int num = 200;
        write(pipefd[1], (void *)&num, sizeof(int));
        sleep(10);
        /* 写完之后关闭写端 */
        close(pipefd[1]);
        _exit(0);
    }
    else if (pid > 0)
    {
        /* 关闭写段 */
        close(pipefd[1]);

        int readNum = 0;
        /* read读的是缓冲区的信息，终端中没有数据会阻塞 man*/
        read(pipefd[0], (void *)&readNum, sizeof(int));
        
        /* read 设置成非阻塞 */
        int flags = fcntl(pipefd[0], F_SETFL);//拿到当前文件描述符的标记
        flags |= O_NONBLOCK;//位运算（或） O_NONBLOCK
        fcntl(pipefd[0], F_SETFL, flags);//设置新的文件标识符
        printf("parent process:readNum:%d\n", readNum);

        /* 写完之后关闭读端 */
        close(pipefd[0]);
        _exit(0);
        
    }
    
    
    
}
/* 阻塞状态：写端不写了，但读端还打开，读端就会阻塞，现在要将它设置成非阻塞 */