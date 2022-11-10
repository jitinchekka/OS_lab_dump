// Fork and pipe
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

void main()
{
	pid_t pid1;
	int fd[2];
	int status = pipe(fd);
	if (status == -1)
	{
		printf("Unable to create pipe\n");
		return;
	}
	pid1 = fork();
	if (pid1 == 0)
	{
		printf("This is the child process\n");
		char str[100];
		close(fd[1]);
		read(fd[0], str, 100);
		printf("%s", str);

	}
	else
	{
		printf("This is the parent process\n");
		char *msg = "I am ur parent";
		close(fd[0]);
		write(fd[1], msg, sizeof(msg));
		wait(NULL);
		printf("Child process has terminated\n");
	}
}