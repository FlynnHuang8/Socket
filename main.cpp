#include <unistd.h>
#include <cstdlib>
#include "smallsh.h"
//程序缓冲区和指针
static char inputBuf[MAXBUF], tokBuf[MAXBUF], *ptr = inputBuf, *tok = tokBuf;
int inarg(char c);
int runcommand(char **cline, int where);
/**
用户输入函数
 **/
int userIn(char *p) {
  int c, count;
  ptr = inputBuf;
  tok = tokBuf;
  //显示提示
  printf("%s", p);
  for (count = 0;;) {
    if ((c = getchar()) == EOF) {
      return EOF;
    }
    if (count < MAXBUF) {
      inputBuf[count++] = c;
    }
    if (c == '\n' && count < MAXBUF) {
      inputBuf[count] = '\n';
      return count;
    }
    if (c == '\n') {
      printf("smallsh: input line too long\n");
      count = 0;
      printf("%s", p);
    }
  }
}
int getTok(char *output) {
  int type;
  for (; *ptr == ' ' || *ptr == '\t'; *ptr++);
  *tok++ = *ptr;
  switch (*ptr) {
    case '\n':type = EOL;
      break;
    case '&':type = AMPERSAND;
      break;
    case ';':type = SEMICOLON;
      break;
    default:type = ARG;
      while (inarg(*ptr))
        *tok++ = *ptr++;
  }
  *tok++ = '\0';
  return type;
}

static char special[] = {' ', '\t', '*', ';', ',', '\n', '\0'};

int inarg(char c) {
  char *wrk;
  for (wrk = special; *wrk != '\0'; wrk++) {
    if (c == *wrk) {
      return 0;
    }
  }
  return 1;
}

void procLine() {
  char *arg[MAXARG + 1];
  int tokType;
  int narg;
  int type;
  for (narg = 0;;) {
    // ?
    switch (tokType = getTok(arg[narg])) {
      case ARG:
        if (narg < MAXARG)
          narg++;
        break;
      case EOL:
      case SEMICOLON:
      case AMPERSAND:type = (tokType == AMPERSAND) ? BACKGROUND : FOREGROUND;
        if (narg != 0) {
          arg[narg] = NULL;
          runcommand(arg, type);
        }
        if (tokType == EOL)
          return;
        narg = 0;
        break;
    }
  }
}

int runcommand(char **cline, int where) {
  int pid, exitStat, ret;
  if ((pid = fork()) < 0) {
    perror("fork fail");
    return -1;
  }
  if (!pid) {
    execvp(*cline, cline);
    perror(*cline);
    exit(127);
  }
  if (where == BACKGROUND) {
    printf("[process id %d ]\n", pid);
    return 0;
  }

  while ((ret = wait(&exitStat)) != pid && ret != -1);
  return ret == -1 ? -1 : exitStat;
}

char *prompt = "command>";
int main(){
  while(userIn(prompt) != EOF)
    procLine();

  return 0;
}