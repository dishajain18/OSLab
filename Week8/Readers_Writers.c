#include<stdio.h>
#include<pthread.h>
#include<semaphore.h>
#include<unistd.h>

sem_t wrt,mutex;
int readcount=0;
int count=1;

void *writer(void *wno) {
	sem_wait(&wrt);
	count *= 2;
	printf("Writer %d modified 'count' to %d\n", (*((int *)wno)), count);
	sem_post(&wrt);
}

void *reader(void *rno) {
	sem_wait(&mutex);
	readcount++;

	if (readcount == 1)
		sem_wait(&wrt);
	sem_post(&mutex);

	printf("Reader %d: read 'count' as %d\n", *((int *)rno), count);

	sem_wait(&mutex);
	readcount--;

	if (readcount == 0)
		sem_post(&wrt);
	sem_post(&mutex);
}

int main()
{
	pthread_t read[10], write[5];
	sem_init(&mutex,0,1);
	sem_init(&wrt, 0, 1);
	int a[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10}; 
	for (int i = 0; i < 10; i++){
		pthread_create(&read[i], NULL, reader, &a[i]);
		if(i<5)
		pthread_create(&write[i], NULL, writer, &a[i]);
	}
	for (int i = 0; i < 10; i++)
		pthread_join(read[i], NULL);
	for (int i = 0; i < 5; i++)
		pthread_join(write[i], NULL);
        sem_destroy(&mutex);
        sem_destroy(&wrt);
	return 0;
}
