// Shortest Job First using non premptive scheduling algorithm
#include<iostream>
#include<algorithm>
using namespace std;
struct process
{
	int pid;
	int at;
	int bt;
	int ct;
	int tat;
	int wt;
};
bool compare(process p1,process p2)
{
	return p1.bt<p2.bt;
}
int main()
{
	int n;
	cout<<"Enter the number of processes: ";
	cin>>n;
	process p[n];
	for(int i=0;i<n;i++)
	{
		cout<<"Enter the details of process "<<i+1<<endl;
		cout<<"Enter the arrival time: ";
		cin>>p[i].at;
		cout<<"Enter the burst time: ";
		cin>>p[i].bt;
		p[i].pid=i+1;
	}
	sort(p,p+n,compare);
	int t=0;
	for(int i=0;i<n;i++)
	{
		p[i].ct=t;
		t+=p[i].bt;
		p[i].tat=t;
		p[i].wt=p[i].tat-p[i].at-p[i].bt;
	}
	cout<<"PID\tAT\tBT\tCT\tTAT\tWT"<<endl;
	return 0;
}