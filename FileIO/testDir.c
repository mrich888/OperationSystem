#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <string.h>
#include <time.h>
#include <dirent.h>

#define BUFFER_SIZE 128

int main()
{
    /* 目的放绝对目录 */
    char buf[BUFFER_SIZE];
    memset(buf, 0, sizeof(buf));
    getcwd(buf, sizeof(buf) - 1);
    /* 打开当前进程的文件夹 */
    DIR *pDir = opendir(buf);
    if (pDir == NULL)
    {
        perror("opendir error");
        return 0;
    }
    /* 开始读目录 */
    struct dirent *pdirent =  NULL;
    if (pdirent == NULL)
    {
        perror("readir error");
    }
    while ((pdirent = readdir(pDir)) != NULL)
    {
        printf("name:%s\n", pdirent->d_name);
    }
    

    /* 打开了文件夹就需要关掉文件夹 */
    closedir(pDir);

    return 0;

}