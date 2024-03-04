#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <string.h>
#include <time.h>

#define BUFFER_SIZE 128

int main()
{
    char buf[BUFFER_SIZE];
    memset(buf, 0, sizeof(buf));

    getcwd(buf, sizeof(buf) - 1);
    printf("buf:%s\n", buf);
    return 0;
}