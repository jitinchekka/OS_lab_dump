// Write a program where you create 2 threads. Consider one global array of size 10. In thread1,  add  values from a[0] to a[4] and store in S1.
// In thread2, add values from a[5] to a[9] and store in s2.
// After completion of thread operation, add s1 and s2 in main function and print the final sum of the given array
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
int global[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
int s1 = 0, s2 = 0;
void *thread1(void *arg)
{
	for (int i = 0; i < 5; i++)
	{
		s1 += global[i];
	}
	printf("Thread 1: Process ID: %d, Thread ID: %lu, S1: %d \n", getpid(), pthread_self(), s1);
	return NULL;
}
void *thread2(void *arg)
{
	for (int i = 5; i < 10; i++)
	{
		s2 += global[i];
	}
	printf("Thread 2: Process ID: %d, Thread ID: %lu, S2: %d \n", getpid(), pthread_self(), s2);
	return NULL;
}
int main()
{
	pthread_t t1, t2;
	pthread_create(&t1, NULL, thread1, NULL);
	pthread_create(&t2, NULL, thread2, NULL);
	pthread_join(t1, NULL);
	pthread_join(t2, NULL);
	printf("Main: Process ID: %d, Thread ID: %lu, S1 + S2: %d \n", getpid(), pthread_self(), s1 + s2);
	return 0;
}