#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

int main() {
   pid_t pid;

    // printf("Parent (PID=%d)\n", getpid());

    // // 使用 fork() 创建子进程
    // pid = fork();

    // if (pid < 0) {
    //     fprintf(stderr, "Fork failed.\n");
    //     return 1;
    // } else if (pid == 0) {
    //     // 子进程的执行路径
    //     printf("Child(PID=%d) \n", getpid());
    // } else {
    //     // 父进程的执行路径
    //     printf("Parent (PID=%d) \n", getpid());
    // }

    // printf("Both parent and child processes continue.\n");

    // 使用 vfork() 创建子进程
    pid = vfork();

    if (pid < 0) {
        fprintf(stderr, "Vfork failed.\n");
        return 1;
    } else if (pid == 0) {
        // 子进程的执行路径
        printf("Child process (PID=%d)\n", getpid());
        _exit(0); // 子进程通过 _exit() 退出，而不是 exit()
    } else {
        // 父进程的执行路径
        printf("Parent process (PID=%d)  \n", getpid());
    }

    printf("Both parent and child processes continue.\n");
}