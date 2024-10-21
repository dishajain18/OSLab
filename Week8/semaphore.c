#include <pthread.h>
#include <stdio.h>
#include <semaphore.h>
sem_t semaphore;
int value;
void *func1( void * param )
{
printf( "Thread 1\n" );
sem_getvalue(&semaphore,&value);
printf("1 : %d\n",value);
sem_post( &semaphore );
sem_getvalue(&semaphore,&value);
printf("1 : %d\n",value);
}
void *func2( void * param )
{
sem_getvalue(&semaphore,&value);
printf("1 : %d\n",value);
sem_wait( &semaphore );
sem_getvalue(&semaphore,&value);
printf("1 : %d\n",value);
printf( "Thread 2\n" );
}
int main()
{
pthread_t threads[2];
sem_init( &semaphore, 0, 1 );
pthread_create( &threads[0], 0, func1, 0 );
pthread_create( &threads[1], 0, func2, 0 );
pthread_join( threads[0], 0 );
pthread_join( threads[1], 0 );
sem_destroy( &semaphore );
}
