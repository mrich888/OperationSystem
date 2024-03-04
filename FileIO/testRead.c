#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <string.h>

#define BUFFER_SIZE 20

int main()
{
    /* 打开文件 */
    int fd = open("./hello.txt", O_RDWR);
    if (fd == -1)
    {
        perror("open error");
    }
    char buffer[BUFFER_SIZE];
    memset(buffer, 0, sizeof(buffer));
    read(fd, buffer, sizeof(buffer));

    printf("buf:%s\n", buffer);
    close(fd);
    return 0;
}