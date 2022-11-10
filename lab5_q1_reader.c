// Reader or client
#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<sys/ipc.h>
#include<sys/shm.h>
#include<sys/types.h>
#include <fcntl.h> 
#include<string.h> 

int main()
{
    int shmid=shmget((key_t)1075,1024,0666);
    if(shmid<0)
    {
        perror("Error with SHM");
        exit(0);
    }
    int *arr=shmat(shmid,NULL,0);
    if(arr==(int*)(-1))
    {
        perror("Error with shmat");
        exit(1);
    }
    int n=arr[0];
    for(int i=1; i<=n; i++)
    {
        if(*(arr+i)%2==0)
        {
            printf("arr[i] = %d Even\n",arr[i]);
        }
        else
        {
            printf("arr[i] = %d Odd\n",arr[i]);
        }
    }
    shmdt(arr);
    shmctl(shmid,IPC_RMID,NULL);
}