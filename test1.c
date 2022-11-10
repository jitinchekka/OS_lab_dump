// Reader writer
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>

pthread_mutex_t mutex;
sem_t wrt;
int readcount = 0;
void *reader(void *args)
{
	pthread_mutex_lock(&mutex);
	readcount++;
	if (readcount == 1)
		sem_wait(&wrt);
	pthread_mutex_unlock(&mutex);

	printf("reader");

	pthread_mutex_lock(&mutex);
	readcount--;
	if (readcount == 0)
		sem_post(&wrt);
	pthread_mutex_unlock(&mutex);
}

void *writer(void *args)
{
	sem_wait(&wrt);
	printf("Writer");
	sem_post(&wrt);
}

void main()
{
	sem_init(&wrt, 0, 1);
	pthread_mutex_init(&mutex, NULL);
	pthread_t r[5], w;
	for (int i = 0; i < 5; i++)
	{
		pthread_create(&r[i], NULL, &reader, NULL);
	}
	pthread_create(&w, NULL, &writer, NULL);
	for (int i = 0; i < 5; i++)
		pthread_join(r[i], NULL);
	pthread_join(w, NULL);
	
	sem_destroy(&wrt);
	pthread_mutex_destroy(&mutex);
}