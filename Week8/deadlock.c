#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>

sem_t s1, s2;

void *first(void *p) {
	sem_wait(&s1);
	printf("First holds s1\n");
	sem_wait(&s2);
	printf("First holds s2\n");
	printf("Thread 1 done\n");
	sem_post(&s1);
}

void *second(void *p) {
	sem_wait(&s2);
	printf("Second holds s2\n");
	sem_wait(&s1);
	printf("Second holds s1\n");
	printf("Thread 2 done\n");
	sem_post(&s2);
}

int main() {
	pthread_t threads[2];
	sem_init(&s1, 0, 1);
	sem_init(&s2, 0, 1);
	pthread_create(&threads[0], 0, first, 0);
	pthread_create(&threads[1], 0, second, 0);
	pthread_join(threads[0], 0);
	pthread_join(threads[1], 0);
	sem_destroy(&s1);
	sem_destroy(&s2);
	return 0;
}
