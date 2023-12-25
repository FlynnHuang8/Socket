#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
    int fd[2];
    pipe(fd); // 创建管道

    if (fork() == 0) { // 子进程
        close(STDIN_FILENO); // 关闭标准输入
        dup(fd[0]); // 重定向标准输入到管道读端
        close(fd[0]); // 关闭原始的读端
        close(fd[1]); // 子进程不需要写端
        printf("childre process\n");
        execlp("./sort", "./sort", NULL); // 执行 sort 程序
        perror("execlp"); // 如果 execlp 失败
        exit(EXIT_FAILURE);
    } else { // 父进程
        close(fd[0]); // 关闭不需要的读端

        // 向管道写入数据
        write(fd[1], "5\n", 2);
        write(fd[1], "1\n", 2);
        write(fd[1], "4\n", 2);


        close(fd[1]); // 关闭写端
        wait(NULL); // 等待子进程结束
    }

    return 0;
}
