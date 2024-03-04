#if 0
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <string.h>

#define BUFFER_SIZE 1000
#define BUFFER_LSEEK 10
int main()
{
    
    /* 创建文件 */
    int fdNew = open("./testOpenCopy.c", O_RDWR | O_CREAT, 0644); 
    if (fdNew == -1)
    {
        perror("opnen error");
    }
    /* 打开文件 */
    int fd = open("./testOpen.c", O_RDWR, 0644); 
    if (fd == -1)
    {
        perror("opnen error");
    }
    /* 读文件 --缓冲区 */
    char buf[BUFFER_SIZE];
    memset(buf, 0, sizeof(buf));

    /* 写文件 */
    int readLen = 0;
    while (1)
    {
        /* 循环读: 10个一读，10个一写 */
        read(fd, buf, BUFFER_LSEEK - 1);
        write(fdNew, buf, readLen);

        if (readLen < BUFFER_LSEEK - 1 || readLen == 0)
        {
            break;
        }    
    }

    close(fd);
    close(fdNew);

    return 0;
}
#endif

#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <string.h>

#define BUFFER_SIZE 10

int main()
{
    /* 打开文件 */
    int fd1 = open("./testOpen.c", O_RDWR);
    if (fd1 == -1)
    {
        perror("open error");
    }
    int fd2 = open("./copyTestOpen.txt", O_RDWR | O_CREAT);
    if (fd2 == -1)
    {
        perror("open error");
    }

    /* 读文件，缓冲区*/
    char buffer[BUFFER_SIZE];
    memset(buffer, 0, sizeof(buffer) - 1);
    /* 文件打开 那文件指针默认在文件开头 */
    int readLen = 0;
    while (1)
    {
        read(fd1, buffer, sizeof(buffer) - 1);
        write(fd2, buffer, readLen);

        if (readLen < BUFFER_SIZE || readLen == 0)
        {
            break;
        }
    }
    return 0;
}