#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

bool is_prime(int n) {
    if (n <= 1) return false;
    for (int i = 2; i * i <= n; i++) {
        if (n % i == 0) {
            return false;
        }
    }
    return true;
}
void* prime(void* param) {

    int * nums = (int*)param;
    int approx = nums[1] - nums [0] + 1;
    int* result = malloc(approx*sizeof(int));  // Allocate memory for the result
    int i=nums[0];
    int j=1;
    while(i<=nums[1])
    {
      if(is_prime(i))
      	{
      	  result[j]=i;
      	  j++;
      	}
      i++;
    }
    result[0]=j; //number of elements in result including 0
    pthread_exit((void*)result); 
}

int main() {
    pthread_t thread;
    printf("Enter start and end (format: start end): ");
    int nums[2];
    scanf("%d %d",&nums[0],&nums[1]);
    int * result;

    pthread_create(&thread, NULL, prime, (void*)nums);

    pthread_join(thread, (void**)&result);
    for(int i=1;i<result[0];i++)
      printf("%d ",result[i]);
    printf("\n");
    return 0;
}

