#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <string.h>
#include <time.h>

#define BUFFER_SIZE 64

void get_file_time(__time_t st_time)
{
    struct tm* info;
    info=localtime(&(st_time));
    printf("%02d %02d %02d:%02d\n",info->tm_mon+1,\
            info->tm_mday,info->tm_hour,info->tm_min);
}

int main()
{
    #if 1
    struct stat bufStat;
    stat("./testCopy.c", &bufStat);
    printf("mode:%d\n", bufStat.st_mode);
    printf("size:%ld\n", bufStat.st_size);

    /* 宏函数区判断,,返回值是1或0，是或者不是 */
    // S_ISREG();

    // printf("atime:%ld\n", bufStat.st_atime);
    // printf("mtime:%ld\n", bufStat.st_mtime);
    // printf("ctime:%ld\n", bufStat.st_ctime);

    /* 调用函数查看：最后一次访问时间 */
    get_file_time(bufStat.st_atime);
    /* 最后一次修改时间 */
    get_file_time(bufStat.st_mtime);
    /* 最后一次改变时间（属性） */
    get_file_time(bufStat.st_ctime);

    /* 配置文件 */
    /* 文件是否被改，md5sum 或者是 时间被修改了 */
    #endif
    #if 0
    /* 库函数 */
    /* md5看 */
    FILE *pfd = popen("md5sum testStat.c", "r");
    if (pfd == NULL)
    {
        perror("popen error");
        return 0;
    }
     
    char buf[BUFFER_SIZE];
    memset(buf, 0, sizeof(buf));
    fread(buf, sizeof(buf) - 1, 1, pfd);
    /* ？：使用正则来过滤 */
    printf("buf:%s\n", buf);
    pclose(pfd);

    #endif 
    return 0;
}