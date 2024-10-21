#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

int fibseries[100];

void* fib(void* param) {
    int n = *(int*)param;  // Dereference the pointer to get the integer value
    printf("Child thread received: %d\n", n);
    
    fibseries[0]=0;
    fibseries[1]=1;
 
    int a = 0, b = 1, temp;
    for (int i = 2; i <= n; i++) 
        fibseries[i] = fibseries[i-1] + fibseries[i-2];
    
}

int main(int argc,char * argv[]) {

    if (argc != 2) {
        fprintf(stderr, "Usage: %s <n>\n", argv[0]);
        return 1;
    }

    pthread_t thread;
    int n = atoi(argv[1]);
    pthread_create(&thread, NULL, fib, (void*)&n);
   
    pthread_join(thread,NULL);
   
    printf("Result from child thread: ");
    for (int i = 0; i < n; i++) {
        printf("%d ",fibseries[i]);
    }
    printf("\n");
    return 0;
}

