// Write a C program to implement round robin scheduling. Consider the context switch overhead while finding the schedule (excluding the overhead at the beginning of the first execution process and at the end of the last execution process)
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <stdbool.h>
struct process
{
	int pid;
	int at;
	int bt;
	int ct;
	int tat;
	int wt;
	int rt; // remaining time
	int resp;
	int flag;
	bool resp_flag;
};
int number_of_process;
int inQueue[4] = {0, 0, 0, 0};
int context_switch_overhead = 0;
struct process p[4];
// Implement queue using linked list
struct node
{
	int process_index;
	struct node *next;
};
struct node *front = NULL, *rear = NULL;
void enqueue(int process_index)
{
	struct node *temp = (struct node *)malloc(sizeof(struct node));
	temp->process_index = process_index;
	temp->next = NULL;
	if (front == NULL)
	{
		front = temp;
		rear = temp;
	}
	else
	{
		rear->next = temp;
		rear = temp;
	}
}
int dequeue()
{
	int process_index;
	if (front == NULL)
	{
		printf("Queue is empty\n");
		exit(0);
	}
	else
	{
		process_index = front->process_index;
		struct node *temp = front;
		front = front->next;
		free(temp);
	}
	return process_index;
}
void display_queue()
{
	struct node *temp = front;
	while (temp != NULL)
	{
		printf("%d ", p[temp->process_index].pid);
		temp = temp->next;
	}
	printf("\n");
}
void display()
{
	struct node *temp = front;
	while (temp != NULL)
	{
		printf("%d ", temp->process_index);
		temp = temp->next;
	}
	printf("\n");
}

void sort()
{
	int i, j;
	struct process temp;
	for (i = 0; i < 4; i++)
	{
		for (j = 0; j < 4 - i - 1; j++)
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
void display_process()
{
	int i;
	printf("PID\tAT\tBT\tCT\tTAT\tWT\tRT\tFLAG\n");
	for (i = 0; i < 4; i++)
	{
		printf("%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\n", p[i].pid, p[i].at, p[i].bt, p[i].ct, p[i].tat, p[i].wt, p[i].resp, p[i].flag);
	}
}

void round_robin(int time_quantum, int context_switch_overhead)
{
	int i = 0, j = 0, count = 0, time = 0, total_time = 0, total_wait = 0, total_turnaround = 0, total_response = 0;
	for (i = 0; i < 4; i++)
	{
		p[i].rt = p[i].bt;
		p[i].flag = 0;
		p[i].resp_flag = false;
	}
	for (i = 0; i < 4; i++)
	{
		if (p[i].at <= time)
		{
			enqueue(i);
		}
	}
	// Print the process details before scheduling
	// printf("\nBefore scheduling\n");
	// display_queue();
	// printf("\n");
	int prev_process_index = p[front->process_index].pid;
	int cs = 0;
	bool switched = false;
	// Start scheduling
	while (front != NULL)
	{
		int index = dequeue();
		if (prev_process_index != p[index].pid)
		{
			cs++;
			prev_process_index = p[index].pid;
			time += context_switch_overhead;
			switched = true;
		}

		if (p[index].resp_flag == false)
		{
			p[index].resp_flag = true;
			p[index].resp = time;
		}
		inQueue[index] = 0;
		if (p[index].rt > time_quantum)
		{
			time += time_quantum;
			p[index].rt -= time_quantum;
			// printf("rt = %d\n", p[index].rt);
		}
		else
		{
			time += p[index].rt;
			p[index].rt = 0;
			inQueue[index] = 1;
			p[index].ct = time;
			p[index].tat = p[index].ct - p[index].at;
			p[index].wt = p[index].tat - p[index].bt;
			p[index].flag = 1;
			p[index].resp = p[index].resp - p[index].at;
			total_time += p[index].tat;
			total_wait += p[index].wt;
			total_turnaround += p[index].tat;
			total_response += p[index].resp;
			count++;
		}

		for (j = 0; j < 4; j++)
		{
			// if not in queue and not executed and arrival time is less than or equal to current time
			if (p[j].flag == 0 && p[j].at <= time && j != index && inQueue[j] == 0)
			{
				enqueue(j);
				inQueue[j] = 1;
			}
		}
		if (p[index].rt > 0)
		{
			enqueue(index);
			inQueue[index] = 1;
		}
		printf("pid =%d Index =%d rt=%d time=%d\n", p[index].pid, index, p[index].rt, time);
	}

	for (i = 0; i < 4; i++)
	{
		if (p[i].flag == 1)
		{
			count++;
		}
	}
	for (i = 0; i < 4; i++)
	{
		if (p[i].flag == 1)
		{
			total_time += p[i].bt;
			total_wait += p[i].wt;
			total_turnaround += p[i].tat;
		}
	}

	printf("\n\nAverage waiting time: %f\n", (float)total_wait / count);
	printf("Average turnaround time: %f\n", (float)total_turnaround / count);
	printf("Average response time: %f\n", (float)total_response / count);
	printf("Number of context switching:%d\n", cs - 1);
}

void main()
{
	int i;
	int time_quantum;
	printf("Enter the details of exactly 4 processes\n");
	for (i = 0; i < 4; i++)
	{
		printf("Enter the pid, arrival time and burst time of process %d\n", i + 1);
		scanf("%d%d%d", &p[i].pid, &p[i].at, &p[i].bt);
		p[i].ct = 0;
		p[i].tat = 0;
		p[i].wt = 0;
		p[i].rt = 0;
		p[i].flag = 0;
	}
	printf("Enter the time quantum\n");
	scanf("%d", &time_quantum);
	printf("Enter the context switch overhead\n");
	scanf("%d", &context_switch_overhead);
	sort();
	round_robin(time_quantum, context_switch_overhead);
	display_process();
}