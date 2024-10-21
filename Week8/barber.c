#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>
#define MAX 5

sem_t customer, barber;
pthread_mutex_t seat;
int frees = MAX;

void *barb(void *args) {
	while (1) {
		if (frees < MAX)
		{
			sem_wait(&customer);
			pthread_mutex_lock(&seat);
			frees++;
			sleep(1.5);
			printf("Barber Free! Seats: %d\n", frees);
			sem_post(&barber);
			pthread_mutex_unlock(&seat);
		}
		else{
			printf("Barber Sleeping...\n");
			sleep(1);
		}

	}
}

void *cust(void *args) {
	while(1){
		
                printf("Customer arrived \n");
		if (frees > 0) {
			pthread_mutex_lock(&seat);
			frees--;
			printf("Customer Waiting! Seats: %d\n", frees);
			sem_post(&customer);
			pthread_mutex_unlock(&seat);
			sem_wait(&barber);
		}
		else{
			printf("Customer Left! Seats: %d\n",frees);
		}
		sleep(rand()%4);
	}
}

int main() {
	pthread_t threads[2];
	sem_init(&barber, 0, 1);
	sem_init(&customer, 0, 0);
	pthread_mutex_init(&seat, 0);
	pthread_create(&threads[0], NULL, barb, NULL);
	pthread_create(&threads[1], NULL, cust, NULL);
	pthread_join(threads[0], NULL);
	pthread_join(threads[1], NULL);
	sem_destroy(&barber);
	sem_destroy(&customer);
	pthread_mutex_destroy(&seat);
	return 0;
}
