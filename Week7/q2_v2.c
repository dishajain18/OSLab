#include <sys/ipc.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/shm.h>

struct shared {
    char c;          // Character to be processed
    int written;     // Status indicator
};

int main()
{
    void* shared_memory = (void*)0;
    struct shared* stuff;
    int shmid=shmget((key_t)1234,sizeof(struct shared),0666|IPC_CREAT);

    int pid=fork();
    if(pid==0)
    {
        shared_memory = shmat(shmid,NULL,0);
        stuff = (struct shared*)shared_memory;
        while(1)
        {


            if(stuff->written==1)
            {
                if(stuff->c>=65 && stuff->c<=90)
                    stuff->c = (stuff->c - 'A' + 1)%26 + 'A';

                else if(stuff->c>=97 && stuff->c<=122)
                    stuff->c = (stuff->c - 'a' + 1)%26 + 'a';

                else{
                    stuff->written=-1;
                    break;
                }

                stuff->written=2;


            }
        }

        shmdt(shared_memory);
        exit(0);

    }
    else{

        shared_memory=shmat(shmid,NULL,0);
        stuff=(struct shared*)shared_memory;
        stuff->written=0;
        while(1){
            if(stuff->written==-1)
                break;

            if(stuff->written==1)
                continue;
            if(stuff->written==2)
            {
                printf("Alphabet changed to: %c\n",stuff->c);
            }
            stuff->written=0;
            printf("Enter alphabet (anything else to exit): ");
            scanf(" %c",&stuff->c);
            stuff->written=1;
        }
        wait(NULL);
        shmdt(shared_memory);
        shmctl(shmid,IPC_RMID,0);
        exit(0);
    }
}
