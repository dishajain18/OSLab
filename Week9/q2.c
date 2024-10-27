#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

void* add(void* param) {

    int * nums = (int*)param;
    int* result = malloc(sizeof(int));  // Allocate memory for the result
    *result = 0;
    for(int i=1;i<=nums[0];i++)
    *result += nums[i];
    
    pthread_exit((void*)result);  // Exit and return the result
}

int main() {
    pthread_t thread;
    printf("No. of elements: ");
    int n;
    scanf("%d",&n);
    printf("Enter the numbers: ");
    int nums[n+1];
    for(int i=1;i<=n;i++)
    scanf("%d",&nums[i]);
    nums[0]=n;
    int* sum;

    pthread_create(&thread, NULL, add, (void*)nums);

    pthread_join(thread, (void**)&sum);

    printf("Result from child thread %d\n",*sum);
    return 0;
}

