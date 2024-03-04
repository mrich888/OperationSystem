#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <string.h>
#include <time.h>
#include <sys/wait.h>


#define BUF_SIZE 10

int main()
{
    char buf[BUF_SIZE];
    memset(buf, 0, BUF_SIZE);
    pid_t pid = fork();
    int status;
    printf("%% ");
    while (fgets(buf, BUF_SIZE, stdin) != NULL)
    {
        //buf[strlen(buf) - 1] = 0;
        if (pid < 0)
        {
            perror("fork error");
        }
        else if (pid == 0)
        {
            /* 子进程 */
            execlp(buf, buf, (char *) 0);
            printf("could not execute:%s", buf);
            exit(-1);
        }
        if (pid = waitpid(pid, &status, 0) < 0)
        {
            perror("Waitpid error");
            printf("%% ");
        }
        exit(0);
    }
    
}