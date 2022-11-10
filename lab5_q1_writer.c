// Writer or server
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/types.h>
#include <fcntl.h>
#include <string.h>

int main()
{
    int n;
    printf("Enter n\n");
    scanf("%d", &n);
    int *arr;
    int shm_id;
    // void* sm;
    key_t key = 1075;
    int shmid = shmget((key_t)key, 1024, 0666 | IPC_CREAT);
    if (shmid < 0)
    {
        printf("Not able to create a shared memory\n");
        exit(0);
    }
    printf("ID of shared memory is %d\n", shm_id);
    arr = shmat(shmid, NULL, 0);
    printf("SM is attached to %p in sender\n", arr);
    if (arr == (int *)-1)
    {
        printf("Not able to attach a shared memory to address space \n ");
        exit(1);
    }
    arr[0] = n;
    for (int i = 1; i <= n; i++)
    {
        *(arr + i) = i;
    }
    printf("The generated values are\n");
    for (int i = 0; i <= n; i++)
    {
        printf("%d ", *(arr + i));
    }
    shmdt(arr); // detach the shared memory
    return 0;
}
