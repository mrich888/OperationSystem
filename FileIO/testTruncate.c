#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <string.h>
#include <time.h>


int main()
{
    int ret = truncate("./xixixi.c", 10);
    if (ret == -1)
    {
        perror("truncate error");
        return 0;
    }
    
    return 0;
}