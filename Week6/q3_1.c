#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <limits.h>
#include <sys/types.h>
#include <sys/stat.h>

#define FIFO_NAME "/tmp/q3Fifo"

int main() {

    if (access(FIFO_NAME, F_OK) == -1) {
        int res = mkfifo(FIFO_NAME, 0777);
        if (res != 0) {
            fprintf(stderr, "Could not create fifo %s\n", FIFO_NAME);
            exit(EXIT_FAILURE);
        }
    }

        char buffer[256];
        while (1) {
            int pipe = open(FIFO_NAME, O_WRONLY);
            printf("User1 types: ");
            scanf(" %[^\n]c",buffer);
            write(pipe, buffer, strlen(buffer));
            close(pipe);
            if (strcmp(buffer, "bye") == 0)
                {
                  unlink(FIFO_NAME);
                  exit(0);
                 }
            pipe = open(FIFO_NAME, O_RDONLY);
            int n=read(pipe, buffer, sizeof(buffer));
            buffer[n]=0;
            printf("User2 says: %s\n", buffer);
            if (strcmp(buffer, "bye") == 0)
                {
                  exit(0);
                 }
            close(pipe);
        }
}
