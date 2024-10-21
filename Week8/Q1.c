#include<stdio.h>
#include<pthread.h>
#include<semaphore.h>
#include<unistd.h>
int buf[10],f,r,val;
sem_t mutex,full,empty;
void *produce(void *arg)
{
	int i;
	for(i=0;i<20;i++)
	{
	        printf("in producer\n");
		sem_wait(&empty);
		sem_wait(&mutex);
		printf("produced item no.%d is %d\n",r,i);
		buf[(++r)%10]=i;
		//sleep(0.1);
		sem_post(&mutex);
		sem_post(&full);
		sem_getvalue(&full,&val);
		printf("fullP %u\n",val);
		
	}
}
void *consume(void *arg)
{
	int item,i;
	for(i=0;i<20;i++)
	{
	        printf("in consumer\n");
		sem_wait(&full);
		sem_wait(&mutex);
		sem_getvalue(&full,&val);
		printf("fullC %u\n",val);
		item=buf[(++f)%10];
		printf("consumed item no.%d is %d\n",f,item);
		//sleep(0.1);
		sem_post(&mutex);
		sem_post(&empty);
	}
}
int main()
{
	pthread_t tid1,tid2;
	sem_init(&mutex,0,1);
	sem_init(&full,0,0);
	sem_init(&empty,0,10);
	pthread_create(&tid1,NULL,produce,NULL);
	pthread_create(&tid2,NULL,consume,NULL);
	pthread_join(tid1,NULL);
	pthread_join(tid2,NULL);
	sem_destroy(&mutex);
	sem_destroy(&full);
	sem_destroy(&empty);
	return 0;
}
