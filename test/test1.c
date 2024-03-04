#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include <error.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#define BUFSIZE 20
#define PIPE_SIZE 2

int main()
{
    /* 创建无名管道数组 */
    int pipefd[BUFSIZE];
    memset(pipefd, 0, sizeof(pipefd));
    /* 创建无名管道 */
    pipe(pipefd);
    /* 写缓冲区 */
    char wBuf[BUFSIZE] = { "hello world!" };
    /* 写缓冲区 */
    char rBuf[BUFSIZE];
    memset(rBuf, 0, sizeof(rBuf));
    pid_t pid;
    pid = fork();
    if (pid < 0)
    {
        perror("fork error");
    }
    else if (pid == 0)
    {
        /* 子进程 --写，关闭读端【0】 */
        close(pipefd[0]);
        int ret = write(pipefd[1], wBuf, sizeof(wBuf));
        if (ret == -1)
        {
            perror("write error");
            exit(-1);
        }
        close(pipefd[1]);
        exit(0);
    }
    else if (pid > 0)
    {
        /* 父进程 --读，关闭写端【1】  */
        close(pipefd[1]);
        int ret = read(pipefd[0], rBuf, sizeof(wBuf));
        if (ret == -1)
        {
            perror("read error");
            exit(-1);
        }
        printf("read:%s\n", rBuf);
        close(pipefd[0]);
        exit(0);
    }
    
    
    return 0;
}