#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

void* odd(void* param) {

    int * nums = (int*)param;
    int* result = malloc(sizeof(int));  // Allocate memory for the result
    *result = 0;
    for(int i=1;i<=nums[0];i++)
    {
      if(nums[i]%2==1)
      *result += nums[i];
    }
    
    pthread_exit((void*)result);  // Exit and return the result
}

void* even(void* param) {

    int * nums = (int*)param;
    int* result = malloc(sizeof(int));  // Allocate memory for the result
    *result = 0;
    for(int i=1;i<=nums[0];i++)
    {
      if(nums[i]%2==0)
      *result += nums[i];
    }
    
    pthread_exit((void*)result);  // Exit and return the result
}

int main() {
    pthread_t oddt,event;
    printf("No. of elements: ");
    int n;
    scanf("%d",&n);
    printf("Enter the numbers: ");
    int nums[n+1];
    for(int i=1;i<=n;i++)
    scanf("%d",&nums[i]);
    nums[0]=n;
    int* evensum;
    int* oddsum;

    pthread_create(&oddt, NULL, odd, (void*)nums);
    pthread_create(&event, NULL, even, (void*)nums);

    pthread_join(oddt, (void**)&oddsum);
    pthread_join(event, (void**)&evensum);

    printf("Result from odd thread %d\n",*oddsum);
    printf("Result from even thread %d\n",*evensum);
    return 0;
}

