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
    int count;
    while(1){

        pipe=open(FIFO_NAME,O_RDONLY);
        read(pipe,&count,sizeof(int));
        if(count>0)
        {
            printf("Do you wish to consume an item (0 or 1)?");
            int c;
            scanf("%d",&c);
            if(c==1)
            {
                count--;
                printf("Item consumed. Current Count: %d\n",count);
                if(count==0)
                    printf("Shelf empty\n");
            }

        }
        close(pipe);
        pipe=open(FIFO_NAME,O_WRONLY);
        write(pipe,&count,sizeof(int));
        close(pipe);

    }

}

