#include <signal.h>#include <unistd.h>#include <cstdio>#include <cstdlib>int nTimes = 0;void p_action();void c_action();int main(){  int pid, ppid;  signal(SIGUSR1, reinterpret_cast<void (*)(int)>(p_action));  switch (pid = fork()) {    case -1:      perror("synchro");      exit(1);    case 0:      signal(SIGUSR1, reinterpret_cast<void (*)(int)>(c_action));      ppid = getppid();      for(;;){        sleep(1);        kill(ppid, SIGUSR1);        pause();      }      break;    default:      for(;;){        pause();        sleep(1);        kill(pid, SIGUSR1);      }  }  return 0;}void p_action(){    printf("Patent caught signal #%d\n", ++nTimes);}void c_action(){    printf("Child caught signal#%d\n", ++nTimes);}