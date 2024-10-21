#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>

struct my_msg_st {
	long int my_msg_type;
	int some_num;
};

char* checkpal(int original)
{ 
  int n = original;
  int remainder;
  int reversed = 0;

    while (n != 0) {
        remainder = n % 10;
        reversed = reversed * 10 + remainder;
        n /= 10;
    }
    if (original == reversed)
     return "Yes";
    
    return "No";
}

int main()
{
	int running = 1;
	int msgid;
	struct my_msg_st some_data;
	long int msg_to_receive = 0;
	msgid = msgget((key_t)1235, 0666 | IPC_CREAT);
	if (msgid == -1) {
		fprintf(stderr, "msgget failed with error: %d\n", errno);
		exit(EXIT_FAILURE);
	}
	while(running) {
		if (msgrcv(msgid, (void *)&some_data, BUFSIZ,msg_to_receive, 0) == -1) {
			fprintf(stderr, "msgrcv failed with error: %d\n", errno);
			exit(EXIT_FAILURE);
		}
		printf("You wrote: %d\n", some_data.some_num);
		if (some_data.some_num < 0) {
			running = 0;
		}
		else
		  printf("Is it a Palindrome? %s\n",checkpal(some_data.some_num));
	}
	if (msgctl(msgid, IPC_RMID, 0) == -1) {
		fprintf(stderr, "msgctl(IPC_RMID) failed\n");
		exit(EXIT_FAILURE);
	}
	exit(EXIT_SUCCESS);
}
