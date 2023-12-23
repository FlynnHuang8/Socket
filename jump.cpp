/*
 * @Author: 黄洪飞 2694342466@qq.com
 * @Date: 2023-12-23 20:57:35
 * @LastEditors: 黄洪飞 2694342466@qq.com
 * @LastEditTime: 2023-12-23 22:17:16
 * @FilePath: /robats/jump.cpp
 * @Description: 
 */

#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <setjmp.h>
#include <unistd.h>

jmp_buf position;

void domenu()
{ // Define the missing function
    printf("1. Continue\n");
}

void goback(int signum)
{
    fprintf(stderr, "Interrupted! Returning to menu.\n");
    longjmp(position, 1);
}

int main()
{
    signal(SIGINT, goback); // Move this line before setjmp

    /* 保存当前的堆栈环境*/
    setjmp(position);
    sleep(5);
    domenu();

    return 0;
}