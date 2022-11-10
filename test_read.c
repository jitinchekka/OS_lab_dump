// #include <stdio.h>
// #include <stdlib.h>
// #include <unistd.h>
// #include <sys/shm.h>
// #include <sys/ipc.h>
// #include <sys/types.h>
// #include <string.h>

// void main()
// {
// 	int shmid = shmget((key_t)1075, 1024, 0666);
// 	if (shmid < 0)
// 	{
// 		printf("Error");
// 	}
// 	char *str = shmat(shmid, NULL, 0);
// 	if(str==(char*)-1)
// 	{
// 		printf("SHM couldn't attach\n");
// 	}
// 	printf("%s", str);
// 	shmdt(str);
// 	shmctl(shmid, IPC_RMID, NULL);
// }
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/types.h>
#include <sys/shm.h>
#include <fcntl.h>
#include <string.h>

void main()
{
	int shmid = shmget((key_t)1075, 1024, 0666);
	if (shmid < 0)
	{
		perror("Error");
		return;
	}
	char *msg = shmat(shmid, NULL, 0);
	if (msg == (char *)-1)
	{
		perror("Couldn't attach");
	}
	printf("%s", msg);
	shmdt(msg);
	shmctl(shmid, IPC_RMID, NULL);
}