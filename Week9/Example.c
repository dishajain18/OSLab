#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

#define NUM_THREADS 5

void* multiply_by_two(void* param) {
    int value = *(int*)param;  // Dereference the pointer to get the integer value
    printf("Child thread received: %d\n", value);
    
    // Multiply by 2
    int* result = malloc(sizeof(int));  // Allocate memory for the result
    *result = value * 2;
    
    pthread_exit((void*)result);  // Exit and return the result
}

int main() {
    pthread_t threads[NUM_THREADS];
    int input_values[NUM_THREADS] = {1, 2, 3, 4, 5};  // Example input values
    int* return_values[NUM_THREADS];  // Array to hold the return values

    // Create threads and pass the input values
    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_create(&threads[i], NULL, multiply_by_two, (void*)&input_values[i]);
    }

    // Wait for each thread to finish and get the return values
    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_join(threads[i], (void**)&return_values[i]);
    }

    // Print the results returned by the child threads
    for (int i = 0; i < NUM_THREADS; i++) {
        printf("Result from child thread %d: %d\n", i, *return_values[i]);
        free(return_values[i]);  // Free the allocated memory for the result
    }

    return 0;
}

