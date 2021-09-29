#include <stdio.h>
#include "../pipex.h"

int	main(int argc, char **argv)
{
	int fd[2];

	setbuf(stdout, NULL);
	// fd[0] = open ("file1", O_RDONLY);
	// dup2(fd[0], STDIN_FILENO);
	pipe(fd);
	printf("pipe 0: %d pipe 1: %d\n", fd[0], fd[1]);

	int pid;
	pid = fork();
	if (pid == 0)
	{
		printf("pipe 0: %d pipe 1: %d\n", fd[0], fd[1]);
		dup2(fd[1], STDOUT_FILENO);
		close(fd[0]);
		close(fd[1]);
		execlp("cat", "cat", "file1", NULL);
	}
	pid = fork();
	if (pid == 0)
	{
		printf("pipe 0: %d pipe 1: %d\n", fd[0], fd[1]);
		dup2(fd[0], STDIN_FILENO);
		close(fd[0]);
		close(fd[1]);
		execlp("grep", "grep", "world", NULL);
	}
	wait(NULL);
	pipe(fd);
	pid = fork();
	if (pid == 0)
	{
		printf("pipe 0: %d pipe 1: %d\n", fd[0], fd[1]);
		dup2(fd[0], STDIN_FILENO);
		close(fd[0]);
		close(fd[1]);
		execlp("grep", "grep", "hello", NULL);
	}
	printf("pipe 0: %d pipe 1: %d\n", fd[0], fd[1]);
}
