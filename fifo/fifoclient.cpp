/*
 * @Author: 黄洪飞 2694342466@qq.com
 * @Date: 2023-12-26 14:45:04
 * @LastEditors: 黄洪飞 2694342466@qq.com
 * @LastEditTime: 2023-12-27 12:43:58
 * @FilePath: /robats/fifo/fifoclient.cpp
 * @Description: 有名管道client
 */
#include <stdio.h>
#include <stdlib.h>

#define FIFO_FILE "sampleFIFO"

int main()
{
    FILE *fp;
    if ((fp = fopen(FIFO_FILE, "w")) == NULL)
    {
        perror("fopen");
        exit(1);
    }

    fputs("Hello, world!", fp);
    fclose(fp);
    return 0;
}