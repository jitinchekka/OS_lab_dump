// // writer
// #include <stdio.h>
// #include <unistd.h>
// #include <stdlib.h>
// #include <sys/ipc.h>
// #include <sys/shm.h>
// #include <sys/types.h>
// #include <fcntl.h>
// #include <string.h>

// void main()
// {
// 	key_t key = 1075;
// 	int shmid = shmget(key, 1024, IPC_CREAT | 0666);
// 	if (shmid < 0)
// 	{
// 		printf("SHM not created");
// 		return;
// 	}
// 	printf("SHMID = %d\n", shmid);
// 	char *arr = shmat(shmid, NULL, 0);
// 	if (arr == (char *)-1)
// 	{
// 		printf("SHM could not attach");
// 		return;
// 	}
// 	char *str = "Shared mem";
// 	strcpy(arr, str);
// 	printf("Test\n");
// 	shmdt(arr);
// }
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/types.h>
#include <fcntl.h>
#include<string.h>
// #include <pthread.h>

void main()
{
	int shmid = shmget((key_t)1075, 1024, 0666 | IPC_CREAT);
	if (shmid < 0)
	{
		printf("Error");
		return;
	}
	char *msg = shmat(shmid, NULL, 0);
	if (msg == (char *)-1)
	{
		printf("Error");
	}
	char *str = "Hi";
	strcpy(msg, str);
	shmdt(msg);
}