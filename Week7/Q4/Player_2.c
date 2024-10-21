#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include "shm_com.h"

int main()
{
	int running = 1;
	void *shared_memory = (void *)0;
	struct shared_use_st *shared_stuff;
	int shmid;
	int turn_no=1;
	srand((unsigned int)getpid());
	shmid = shmget((key_t)1234, sizeof(struct shared_use_st), 0666 | IPC_CREAT);
	if (shmid == -1) {
		fprintf(stderr, "shmget failed\n");
		exit(EXIT_FAILURE);
	}
	shared_memory = shmat(shmid, (void *)0, 0);
	if (shared_memory == (void *)-1) {
		fprintf(stderr, "shmat failed\n");
		exit(EXIT_FAILURE);
	}
	printf("Memory attached at %X\n", *((int*)shared_memory));
	shared_stuff = (struct shared_use_st *)shared_memory;
	printf("You are O\n");
	while(running) {
		if (shared_stuff->whose_turn==2) {
		        printf("Current Matrix: \n");
		        print_matrix(shared_stuff->matrix);
		        if(shared_stuff->who_won=='X')
		           {
		             printf("PLAYER 1 WINS\n");
		             break;
		           }
		        printf("Your move: ");
		        int i,j;
		        scanf("%d,%d",&i,&j);
		        shared_stuff->matrix[i][j]='O';
		        print_matrix(shared_stuff->matrix);
		        shared_stuff->who_won=check_winner(shared_stuff->matrix);
		        if(shared_stuff->who_won=='O')
		           {
		             printf("PLAYER 2 WINS\n");
		             shared_stuff->whose_turn = 1;
		             break;
		           }
			sleep(1); /* make the other process wait for us ! */
			shared_stuff->whose_turn = 1;
			if (turn_no==4) {
				running = 0;
			}
			turn_no++;
		}
	}
	if(shared_stuff->who_won=='*')
        printf("IT'S A TIE\n");

	if (shmdt(shared_memory) == -1) {
		fprintf(stderr, "shmdt failed\n");
		exit(EXIT_FAILURE);
	}

	exit(EXIT_SUCCESS);
}
