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
    int ret = access("./testfifo", F_OK);
    if (ret == -1)
    {
        perror("mkfifo error");
        _exit(-1);
    }   
    
    int fd =open("./testfifo", O_RDWR | O_NONBLOCK);
    if (fd == -1)
    {
        perror("open error");
        _exit(-1);
    }
    char buf[BUFF_SIZE];
    
    while (1)
    {
        memset(buf, 0, sizeof(buf));
        int bytes = read(fd, buf, sizeof(buf) - 1);
        if (bytes < 0)
        {
            perror("read error");
            _exit(-1);
        }
        
    }
    
    printf("buf:%s\n", buf);

    sleep(5);
   // close(fd);
    return 0;
}
