#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main()
{
  pid_t pid;
  char *message;
  int n;
  printf("fork program starting\n");
  pid = fork();
  switch(pid)
  {
        case -1:
		perror("fork failed");
		exit(1);
	case 0:
		message = "This is the child";
		n = 5;
	        break;
	default:
		message = "This is the parent";
		n = 3;
		break;
   }
   for(; n > 0; n--) 
   {
        puts(message);
        sleep(1);
   }
   exit(0);
}

//the last "this is a child" message comes mixed in with the terminal shell prompt i.e 

/*fork program starting
This is the parent
This is the child
This is the parent
This is the child
This is the parent
This is the child
This is the child
student@dblab-cp30:~/Desktop/220905554/Week5$ This is the child*/

