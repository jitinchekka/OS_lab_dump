// Define one global array and take input from the user.
// Perform the following operations in a different process.

// (i) Parent Process:-

// (a)Print the elements, address of the elements and find the minimum element in the array

// (b) Print id and parent id of the process

// (ii) Child Process:-

//   (a)Print the elements, address of the elements and find the maximum element in the array,

//    (b)print id and parent id,
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
int main()
{
	int n;
	scanf("%d", &n);
	int arr[n];
	for (int i = 0; i < n; i++)
	{
		scanf("%d", &arr[i]);
	}
	pid_t pid;
	if ((pid = fork()) != 0)
	{
		// parent
		// parent process
		printf("The elements of the array and address are\n");
		int min_elem = arr[0];
		for (int i = 0; i < n; i++)
		{
			printf("%d %p", arr[i], &arr[i]);
			if (arr[i] < min_elem)
			{
				min_elem = arr[i];
			}
		}
		printf("\nThe pid is %d and ppid is %d", getpid(), getppid());
	}
	else
	{
		// Child
		printf("The elements of the array and address are\n");
		int max_elem = arr[0];
		for (int i = 0; i < n; i++)
		{
			printf("%d %p", arr[i], &arr[i]);
			if (arr[i] > max_elem)
			{
				max_elem = arr[i];
			}
		}
		printf("The pid is %d and ppid is %d", getpid(), getppid());
	}
}