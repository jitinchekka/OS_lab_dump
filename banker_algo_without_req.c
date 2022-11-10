// Implement Banker's algorithm
// Define the ALLOCATION and  MAX matrix  and the AVAILABLE array. Find the NEED matrix. You must ensure that your  initial allocation will always lead to the system in  safe state.
// Now, take the input from the user for any process as additional request. Find that this request will lead to safe  or unsafe state.

#include <stdio.h>
void main()
{
	int n, m; // number of processes and resources types
	printf("Enter the number of processes: ");
	scanf("%d", &n);
	printf("Enter the number of resources types: ");
	scanf("%d", &m);
	int available[m];	   // available resources
	int available_copy[m]; // copy of available resources
	int need[n][m];		   // need matrix
	int allocation[n][m];  // allocation matrix
	int max[n][m];		   // max matrix
	int i, j;
	printf("Enter the total resources:\n");
	for (i = 0; i < m; i++)
	{
		scanf("%d", &available[i]);
		available_copy[i] = available[i];
	}
	printf("Enter the allocation matrix:\n");
	for (i = 0; i < n; i++)
	{
		for (j = 0; j < m; j++)
		{
			scanf("%d", &allocation[i][j]);
		}
	}
	printf("Enter the max matrix:\n");
	for (i = 0; i < n; i++)
	{
		for (j = 0; j < m; j++)
		{
			scanf("%d", &max[i][j]);
		}
	}
	// calculate the need matrix
	for (i = 0; i < n; i++)
	{
		for (j = 0; j < m; j++)
		{
			need[i][j] = max[i][j] - allocation[i][j];
		}
	}
	// print the need matrix
	printf("Need matrix:\n");
	for (i = 0; i < n; i++)
	{
		for (j = 0; j < m; j++)
		{
			printf("%d ", need[i][j]);
		}
		printf("\n");
	}

	// calculate the available array
	for (int j = 0; j < m; j++)
	{
		int sum = 0;
		for (int i = 0; i < n; i++)
		{
			sum += allocation[i][j];
		}
		available[j] -= sum;
	}
	// Print available array
	int finish[n];
	int finished = 0;
	while (finished != n)
	{
		int flag = 0;
		for (int i = 0; i < n; i++) //process number
		{
			if (finish[i] == 1)
				continue;
			int j;
			for (j = 0; j < m; j++)
			{
				if (need[i][j] > available[j])
				{
					break;
				}
			}
			if (j == m) // all the resources are available
			{
				for (int k = 0; k < m; k++)
				{
					available[k] += allocation[i][k];
				}
				finish[i] = 1;
				finished++;
				printf("P%d ", i + 1);
				flag = 1;
			}
		}
		if (flag == 0)
		{
			printf("\nUnsafe state\n");
			break;
		}
	}
	printf("Safe state");
}
