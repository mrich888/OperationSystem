#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>

int main()
{
    /* 打开文件 */
    int fd = open("./hello.txt", O_RDWR | O_CREAT, 0644); // O_RDWR | O_CREA可选和必选
    if (fd == -1)
    {
        perror("opnen error");
    }

    return 0;
}