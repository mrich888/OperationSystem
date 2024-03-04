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
#include <sys/mman.h>

#define BUFF_SIZE 20

int main()
{
     /* 打开文件 */
    int fd = open("./mmap.txt", O_RDWR | O_CREAT, 0644);
    if (fd == -1)
    {
        perror("open error");
    }
    /* 文件映射 */
    void * ptr =  mmap(NULL, 1024, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    if (ptr == MAP_FAILED)
    {
        perror("mmap error");
        /* 进程退出 */
        _exit(-1);
    }
    /* 关闭文件 */
    close(fd);
    
    pid_t pid = fork();
    if (pid < 0)
    {
        perror("fork error");
    }

    if (pid == 0)
    {
        /* 子进程 */
        strcpy((char *)ptr, "666");
        
    }
    else if (pid > 0)
    {
        /* 父进程,行缓存 */
        printf("ptr:%s\n", (char *)ptr); //强转
        sleep(4);
    }
    int ret = munmap(ptr, 1024);
    if (ret ==-1)
    {
        perror("munmap error");
        _exit(-1);
    }
    
    return 0;
}