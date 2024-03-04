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

#define BUFF_SIZE 20

int main()
{
    int fd = access("./testfifo", F_OK);
    if (fd == -1)
    {
        int fd = mkfifo("./testfifo", O_RDWR);
        if (fd == -1)
        {
            perror("open error");
            _exit(-1);
        }
    }   

    char buf[BUFF_SIZE];
    memset(buf, 0, sizeof(buf));
    strncpy(buf, "hello word", sizeof(buf) - 1);
    write(fd, buf, strlen(buf));

    close(fd);
    return 0;
}
/* 一个读一个写 */