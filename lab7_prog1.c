// Write a program where you create 2 processes. In each process, create two threads. In each thread, consider one global variable and one local variable. Perform some operation  in local and global variable.
// Print the process id, and thread id of the respective process and thread, local variable address, global variable address and values of local and global variables in each thread.
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
int global = 10;
void *thread1(void *arg)
{
	int local = 20;
	printf("arg = %d\n", *(int*)arg);
	printf("Thread 1: Process ID: %d, Thread ID: %lu, Local Variable Address: %p, Global Variable Address: %p, Local Variable Value: %d, Global Variable Value: %d \n", getpid(), pthread_self(), &local, &global, local, global);
	return NULL;
}
void *thread2(void *arg)
{
	int local = 30;
	printf("Thread 2: Process ID: %d, Thread ID: %lu, Local Variable Address: %p, Global Variable Address: %p, Local Variable Value: %d, Global Variable Value: %d \n", getpid(), pthread_self(), &local, &global, local, global);
	return NULL;
}
int main()
{
	int local = 40;
	pid_t pid;
	pid = fork();
	if (pid == 0)
	{
		pthread_t t1, t2;
		int x = 192;
		pthread_create(&t1, NULL, &thread1, NULL);
		pthread_create(&t2, NULL, &thread2, NULL);
		pthread_join(t1, NULL);
		pthread_join(t2, NULL);
	}
	else
	{
		wait(NULL);
		pthread_t t1, t2;
		pthread_create(&t1, NULL, &thread1, NULL);
		pthread_create(&t2, NULL, &thread2, NULL);
		pthread_join(t1, NULL);
		pthread_join(t2, NULL);
	}
	printf("Main: Process ID: %d, Thread ID: %lu, Local Variable Address: %p, Global Variable Address: %p, Local Variable Value: %d, Global Variable Value: %d \n", getpid(), pthread_self(), &local, &global, local, global);
	return 0;
}