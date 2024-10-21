#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>

int main()
{
  pid_t pid;
  char * message;
  printf("q1 Fork process starting\n");
  pid = fork();
  if(pid<0)
  {
    perror("q1 Fork failed\n");
    exit(-1);
  }
  else if(pid==0)
  {
    for(int i=0;i<5;i++)
      { 
        sleep(1);
        printf("q1 Child %d\n",i); 
      }
    exit(0);
  }
  else
  {
    int status;
    wait(&status);
    printf("I'm Parent q1\n");
    printf("q1 Child returned: %d\n",status);
  }
}
