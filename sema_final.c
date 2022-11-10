#include <stdio.h>
#include <stdlib.h>
#include <semaphore.h>
#include <pthread.h>
// A1,B1,B2,A2 -- correct
// B1,A1,A2,B2 -- correct
sem_t s1, s2;
void *thread_fn1(void *arg)
{
	sem_wait(&s1);
	printf("A1\n");
	sem_wait(&s1);
	printf("A2\n");
	sem_post(&s2);
}

void *thread_fn2(void *arg)
{
	sem_wait(&s2);
	printf("B1\n");
	sem_post(&s1);
	sem_wait(&s2);
	printf("B2\n");
	sem_post(&s1);
}

void main()
{
	pthread_t t1, t2;
	sem_init(&s1, 0, 1);
	sem_init(&s2, 0, 1);
	int first;
	printf("Which thread should run first? 1 or 2? ");
	scanf("%d", &first);
	if (first == 1)
	{
		pthread_create(&t1, NULL, &thread_fn1, NULL);
		pthread_create(&t2, NULL, &thread_fn2, NULL);
	}
	else
	{
		pthread_create(&t2, NULL, &thread_fn2, NULL);
		pthread_create(&t1, NULL, &thread_fn1, NULL);
	}
	sem_destroy(&s1);
	sem_destroy(&s2);
	pthread_join(t1, NULL);
	pthread_join(t2, NULL);
}