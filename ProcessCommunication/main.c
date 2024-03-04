#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <error.h>
#include <wait.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#define BUFFER_SIZE 10

int main()
{
    int num =100;
    pid_t pid = fork();
    /* 本身就是一个子进程和一个父进程，并且进程间相互独立，理论上哪个进程先执行不知道 */
    if (pid < 0)
    {
        /* 失败 */
        perror("fork error");
        _exit(-1);
    }
    
    if (pid == 0)
    {
        printf("childPid:num = %d\n", num); 

        num += 100;
        printf("childPid:num = %d\n", num); 

        /* 写进文件:首先要创建一个文件 */ 
        int fd = open("./write.txt", O_RDWR | O_CREAT, 0644);
        if (fd == -1)
        {
            perror("opnen error");
        }
        /* 开始写 */
        write(fd, (void *)&num,sizeof(num));
        close(fd);
    }
    else if (pid > 0)
    {
        
        printf("parentPid process: num = %d\n", num); 
        sleep(1);
        /* 打开文件 */
        int fd = open("./write.txt", O_RDWR);
        if (fd == -1)
        {
            perror("open error");
        }
        /* 读 */
        int readNum = 0;
        read(fd, (void *)&readNum, sizeof(readNum));
        close(fd);
        printf("parentPid process: readNum = %d\n", readNum); 
    }

    wait(NULL);
    printf("hello world\n");
    return 0;
}