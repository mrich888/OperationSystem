#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <string.h>

int main()
{
    #if 0
    /* 打开文件 */
    int fd = open("./hello.txt", O_RDWR);
    if (fd == -1)
    {
        perror("open error");
    }
    /* 向文件中写数据 */
    
    char * ptr = "hello world!\n";
    /* 不能加一，遇到反斜杠0会导致下面的输不出来 */
    int bytes = write(fd, ptr, strlen(ptr)); 
    if (bytes < 0)
    {
        perror("write error");
    }
    else
    {
        printf("bytes:%d\n", bytes);
    }
    /* 关闭文件 */
    close(fd);
    #endif
    #if 0
    /* 清空 */
    int fd = open("./hello.txt", O_RDWR | O_TRUNC);
    if (fd == -1)
    {
        perror("open error");
    }
    /* 关闭文件 */
    close(fd);
    #endif
    #if 1
    /* 以追加的方式打开 */
    int fd = open("./hello.txt", O_RDWR | O_APPEND);
    if (fd == -1)
    {
        perror("open error");
    }
    char ptr[] = "123\n";
    int bytes = write(fd, ptr, sizeof(ptr)); 
    /* 关闭文件 */
    close(fd);
    #endif
    return 0;
}
