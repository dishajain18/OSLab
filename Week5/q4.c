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
    printf("Child PID: %d\n", getpid());  
    exit(0);
  }
 
  else
  {
    printf("Parent PID: %d\n", getpid());
    printf("Parent Sleeping for 5 seconds...\n");
    sleep(5);
    printf("\nParent terminating...\n");
   //execlp("ps","ps",NULL); instead of this while running ./q4 we'll run it in background i.e ./q4 &  , this way i can use the terminal to type ps command directly
    exit(0);
    //sleep(5); 
    //printf("\nParent terminating...\n");
   }

    return 0;
}


//NOTE: You cannot run any other instruction after exec function. After exec, parent process can continue if wait was mentioned like in q2 but here, after execlp no other command like sleep or printf are working
