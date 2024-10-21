#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <stdbool.h>
#define MAX_TEXT 512

struct my_msg_st {
	long int my_msg_type;
	char alpha;
	bool changed;
};

int main()
{
	int running = 1;
	struct my_msg_st some_data;
	int msgid;
	long int msg_to_receive = 0;
	int p_id = fork();
	
	if(p_id==0)
	{  
	        sleep(10);
	        printf("IN CHILD\n");
	        msgid = msgget((key_t)1236, 0666 | IPC_CREAT);
		if (msgid == -1) {
			fprintf(stderr, "msgget failed with error: %d\n", errno);
			exit(EXIT_FAILURE);
		  }
		while(running) {
			if (msgrcv(msgid, (void *)&some_data, BUFSIZ,msg_to_receive, 0) == -1) {
				fprintf(stderr, "msgrcv failed with error: %d\n", errno);
				exit(EXIT_FAILURE);
			}
			printf("Parent wrote: %c", some_data.alpha);
			if (some_data.alpha == '$') {
				running = 0;
			}
			else
			{
			  char temp = some_data.alpha;
			  if(temp>65 && temp<90)
			    temp = 65 + (temp - 65 + 1)%26;
			  else if(temp>97 && temp<122)
			    temp = 97 + (temp - 97 + 1)%26;
			  some_data.alpha = temp;
			  if (msgsnd(msgid, (void *)&some_data, MAX_TEXT, 0) == -1) {
				fprintf(stderr, "msgsnd failed\n");
				exit(EXIT_FAILURE);
			  }
			}
			sleep(1);
		}
		if (msgctl(msgid, IPC_RMID, 0) == -1) {
			fprintf(stderr, "msgctl(IPC_RMID) failed\n");
			exit(EXIT_FAILURE);
		}
		exit(EXIT_SUCCESS);
		  
        }
	
	else if(p_id>0)
	{  
		msgid = msgget((key_t)1236, 0666 | IPC_CREAT);
		if (msgid == -1) {
			fprintf(stderr, "msgget failed with error: %d\n", errno);
			exit(EXIT_FAILURE);
		}
		while(running) {
			printf("Enter some text ($ to exit):");
			scanf("%c",&some_data.alpha);
			some_data.my_msg_type = 1;
			some_data.changed = false;
			if (msgsnd(msgid, (void *)&some_data, MAX_TEXT, 0) == -1) {
				fprintf(stderr, "msgsnd failed\n");
				exit(EXIT_FAILURE);
			}
			if (some_data.alpha == '$') 
				running = 0;	
			else
			{ 
			  sleep(3);
			  while(1)
			  {
				  if (msgrcv(msgid, (void *)&some_data, BUFSIZ,msg_to_receive, 0) == -1) {
					fprintf(stderr, "msgrcv failed with error: %d\n", errno);
					exit(EXIT_FAILURE);
				   }
				   
				   if(some_data.changed == true)
				      break;
		          }
			  printf("Next Char: %c", some_data.alpha);
			}
			 
		}
		
		exit(EXIT_SUCCESS);
	}
	
	else
	  {
	    perror("Could not fork");
	    exit(EXIT_FAILURE);
	  }
	exit(EXIT_SUCCESS);
}
