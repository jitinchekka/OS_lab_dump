// First come first serve scheduling algorithm
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
// sort using bubble sort by arrival time
void sort(struct process *p, int n)
{
	int i, j;
	struct process temp;
	for (i = 0; i < n - 1; i++)
	{
		for (j = 0; j < n - i - 1; j++)
		{
			if (p[j].at > p[j + 1].at)
			{
				temp = p[j];
				p[j] = p[j + 1];
				p[j + 1] = temp;
			}
		}
	}
}
void display(struct process *p, int n)
{
	int i;
	printf("\nPID\tAT\tBT\tCT\tTAT\tWT\n");
	int avg_waiting_time = 0, avg_turnaround_time = 0;
	for (i = 0; i < n; i++)
	{
		printf("%d\t%d\t%d\t%d\t%d\t%d\n", p[i].pid, p[i].at, p[i].bt, p[i].ct, p[i].tat, p[i].wt);
		avg_waiting_time += p[i].wt;
		avg_turnaround_time += p[i].tat;
	}
	printf("Average turnaround time: %f\n", (float)avg_turnaround_time / n);
	printf("\nAverage waiting time: %f\n", (float)avg_waiting_time / n);
}
int main()
{
	int n, i;
	printf("Enter the number of processes: ");
	scanf("%d", &n);
	struct process *p = (struct process *)malloc(n * sizeof(struct process));
	for (i = 0; i < n; i++)
	{
		printf("Enter the details of process %d:\n", i + 1);
		printf("Enter the arrival time: ");
		scanf("%d", &p[i].at);
		printf("Enter the burst time: ");
		scanf("%d", &p[i].bt);
		p[i].pid = i + 1;
	}
	sort(p, n);
	int t = 0, j = 0, k = 0;
	for (i = 0; i < n; i++)
	{
		if (p[i].at <= t)
		{
			p[i].ct = t + p[i].bt;
			p[i].tat = p[i].ct - p[i].at;
			p[i].wt = p[i].tat - p[i].bt;
			t = p[i].ct;
			j++;
		}
		else
		{
			p[i].ct = p[i].at + p[i].bt;
			p[i].tat = p[i].ct - p[i].at;
			p[i].wt = p[i].tat - p[i].bt;
			t = p[i].ct;
			k++;
		}
	}
	printf("\n\nThe scheduling algorithm is First Come First Serve\n");
	printf("\nThe total number of processes that arrived is %d\n", j);
	printf("\nThe total number of processes that arrived and executed is %d\n", k);
	display(p, n);
	return 0;
}
