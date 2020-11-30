#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <fcntl.h>
#include <unistd.h>

static void sighandler(int signo){
  char buff [] = "Program exited due to SIGINT";
  if (signo == SIGINT){
    int fd = open("./msg.txt",  O_CREAT | O_WRONLY | O_APPEND, 0777);
    int bytes = write(fd,buff,sizeof(buff));
    close(fd);
    exit(0);
  }
  if (signo == SIGUSR1)
    printf("Parent PID: %d\n", getppid());
}



int main(){
  signal(SIGINT, sighandler);
  signal(SIGUSR1, sighandler);
  while (1){
    printf("PID: %d\n", getpid());
    sleep(1);
  }
}
