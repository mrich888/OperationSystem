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
    /* F_OK用来判断文件是否存在 */
    int ret = access("./testCopy.c", F_OK);
    if (ret != 0)
    {
        perror("access error");
    }
    printf("ret:%d\n", ret);
    return 0;
}