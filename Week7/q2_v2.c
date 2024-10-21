#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/wait.h>

struct shared_use_st {
    char alphabet;
    int written_by_you;
};

int main() {
    void *shared_memory = (void *)0;
    struct shared_use_st *shared_stuff;
    int shmid;

    // Create shared memory
    shmid = shmget((key_t)1234, sizeof(struct shared_use_st), 0666 | IPC_CREAT);
    if (shmid == -1) {
        fprintf(stderr, "shmget failed\n");
        exit(EXIT_FAILURE);
    }

    // Attach to shared memory
    shared_memory = shmat(shmid, (void *)0, 0);
    if (shared_memory == (void *)-1) {
        fprintf(stderr, "shmat failed\n");
        exit(EXIT_FAILURE);
    }

    shared_stuff = (struct shared_use_st *)shared_memory;
    shared_stuff->written_by_you = 0;

    // Fork the process to create a child
    pid_t pid = fork();

    if (pid < 0) {
        fprintf(stderr, "Fork failed\n");
        exit(EXIT_FAILURE);
    }

    // Parent process
    if (pid > 0) {
        char c;
        while (1) {
            printf("Enter an English alphabet or '#' to exit: ");
            scanf(" %c", &c);
            if (c == '#') {
                // Notify child to exit
                shared_stuff->alphabet = '#';
                shared_stuff->written_by_you = 1;
                break; // Exit the loop
            }

            shared_stuff->alphabet = c;
            shared_stuff->written_by_you = 1;

            // Wait for the child to respond
            while (shared_stuff->written_by_you);

            // Display the response from the child
            printf("Child responded with: %c\n", shared_stuff->alphabet);
        }

        // Wait for the child process to finish
        wait(NULL);
    } 
    // Child process
    else {
        while (1) {
            // Wait for the parent to write
            while (shared_stuff->written_by_you == 0) {
                sleep(1);
            }

            // Process the input character
            char cc = shared_stuff->alphabet;
            if (cc == '#') {
                break; // Exit the child loop if '#' is received
            }

            if ((cc >= 'a' && cc <= 'z') || (cc >= 'A' && cc <= 'Z')) {
                shared_stuff->alphabet = (cc == 'z') ? 'a' : (cc == 'Z') ? 'A' : cc + 1;
            } else {
                shared_stuff->alphabet = '*'; // invalid
            }
            shared_stuff->written_by_you = 0; // Indicate response is ready
        }
    }

    // Detach and remove shared memory
    if (shmdt(shared_memory) == -1) {
        fprintf(stderr, "shmdt failed\n");
        exit(EXIT_FAILURE);
    }
    shmctl(shmid, IPC_RMID, 0);

    return 0;
}
