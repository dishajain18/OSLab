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
    printf("In Child");
    printf("\nChild: %d",getpid());
    printf("\nParent: %d",getppid());
  }
  else
  {
    wait(NULL);
    printf("\nIn Parent");
    printf("\nChild: %d",pid);
    printf("\nParent: %d\n",getpid());
  }
}
