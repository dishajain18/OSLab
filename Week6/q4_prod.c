#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>
#include <assert.h>
#include <limits.h>
#include <sys/wait.h>
#define MAX 5
#define FIFO_NAME "/tmp/q4Fifo"

int main()
{
    int pipe;
    if(access(FIFO_NAME,F_OK)==-1)
    {
        if(mkfifo(FIFO_NAME,0777)==-1)
        {
            perror("Could not create fifo");
            exit(-1);
        }
    }
    int count=MAX;
    printf("Current count: %d\n",count);
    while(1){
        pipe=open(FIFO_NAME,O_WRONLY);
        write(pipe,&count,sizeof(int));
        close(pipe);

        pipe=open(FIFO_NAME,O_RDONLY);
        read(pipe,&count,sizeof(int));
        close(pipe);
        if(pipe==-1)
        {
            perror("Could not open pipe");
            exit(-1);
        }
        if(count<MAX)
        {
            printf("Do you wish to enter an item (0 or 1)?");
            int c;
            scanf("%d",&c);
            if(c==1)
            {
                count++;
                printf("Item added. Current Count: %d\n",count);
                if(count==MAX)
                    printf("Shelf full\n");
            }

        }

    }

}

