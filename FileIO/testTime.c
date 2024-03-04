#include <stdio.h>
#include <time.h>
#include <fcntl.h>
#include <unistd.h>

/* 调试标记是否存在 */
int g_debug = 0;
/* 日志：就是文件 */
/* 打开日志文件 */
void log_init()
{
    time_t now;
    /* 避免野指针 */
    struct tm *ptm = NULL;

#define DEBUG_FLAG "./my_debug.flag"

    /* access成功返回0 */
    if (!access(DEBUG_FLAG, F_OK))
    {
        g_debug = 1;
    }

    if (!g_debug)
    {
        return ;
    }
#define DEBUG_FILE "./my_debug.log"
    if (/* condition */)
    {
        /* code */
    }
    
    

}
/* */
void log_close()
{

}


int main()
{
    struct * tm  =

    return 0;
}