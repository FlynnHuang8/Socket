/*
 * @Author: 黄洪飞 2694342466@qq.com
 * @Date: 2023-12-26 14:04:43
 * @LastEditors: 黄洪飞 2694342466@qq.com
 * @LastEditTime: 2023-12-26 14:40:26
 * @FilePath: /robats/fifo/fifoserver.cpp
 * @Description: 有名管道server端
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>

#define FIFO_FILE "sampleFIFO"

int main()
{
    FILE *fp;
    char readbuf[80];
    /*Creat the FIFO if it does not exist*/
    umask(0);
    mknod(FIFO_FILE, S_IFIFO|0666, 0);

    while(1){
        /*打开有名管道*/
        fp = fopen(FIFO_FILE, "r");
        
        /*读取有名管道中的数据*/
        fgets(readbuf, 80, fp);
        printf("Received string: %s\n", readbuf);
        /*关闭有名管道*/
        fclose(fp);

    }
    return 0;
}