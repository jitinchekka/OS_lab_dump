#include <stdio.h>
#include <stdlib.h>

struct process
{
	int pid;
	int at;
	int bt;
	int ct;
	int tat;
	int wt;
};

void sort(struct process *p, int n)
{
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n - 1 - i; j++)
		{
			if (p[j].at > p[j + 1].at)
			{
				struct process temp = p[j];
				p[j] = p[j + 1];
				p[j + 1] = temp;
			}
		}
	}
}
void main()
{
	int n;
	scanf("%d", &n);
	struct process p[n];
	for (int i = 0; i < n; i++)
	{
		printf("Enter the details of process %d", i + 1);
		p[i].pid = i + 1;
		printf("Enter Arrival time: ");
		scanf("%d", &p[i].at);
		printf("Enter Burst time: ");
		scanf("%d", &p[i].at);
	}
}