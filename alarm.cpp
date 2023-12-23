#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <string.h>
#include <setjmp.h>

#define TRUE 1
#define FALSE 0
#define BELLS "\007\007\007"

int alarm_flag = FALSE;

void setFlag(int signum) {
    alarm_flag = TRUE;
}


int main(int argc, char* argv[]) {
    int nsecs;
    int i;
    if (argc < 2) {
        fprintf(stderr, "Usage:tml $minutes message\n");
        exit(1);
    }
    if ((nsecs = atoi(argv[1]) * 6) <= 0) {
        fprintf(stderr, "Invalid time\n");
        exit(2);
    }
    signal(SIGALRM, setFlag);
    alarm(nsecs);

    pause();
    if(alarm_flag){
        printf(BELLS);
        for(i = 0; i < argc; i++){
            printf("%s\n", argv[i]);
        }
    }
    exit(0);
}