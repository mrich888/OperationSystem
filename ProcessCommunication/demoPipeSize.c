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
    int pipefd[PIPE_SIZE];
    memset(pipefd, 0, sizeof(pipefd));

    pipe(pipefd);
    /* 查看缓冲区大小 */
    long bufferSize = fpathconf(pipefd[0], _PC_PIPE_BUF);
    printf("bufferSize:%ld\n", bufferSize);

    bufferSize = fpathconf(pipefd[1], _PC_PIPE_BUF);
    printf("bufferSize:%ld\n", bufferSize);

    return 0;
}