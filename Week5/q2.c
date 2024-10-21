#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>

int main()
{
  pid_t pid;
  char * message;
  printf("q2 Fork process starting\n");
  pid = fork();
  if(pid<0)
  {
    perror("q2 Fork failed\n");
    exit(-1);
  }
  else if(pid==0)
  {
    execlp("./q1","./q1",NULL);
    exit(0);
  }
  
  else
  {
    int status;
    wait(&status);
    printf("I'm Parent q2\n");
    printf("q2 Child returned: %d\n",status);
  }
}
