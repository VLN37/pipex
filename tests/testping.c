#include <sys/wait.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>

int	main(int argc, char *argv[])
{
	int	pipefd[2];
	int	pid1;
	int	pid2;

	pipe(pipefd);
	pid1 = fork();
	if (pid1 < 0)
		return (1);

	if (pid1 == 0)
	{
		//child process
		dup2(pipefd[1], STDOUT_FILENO);
		close(pipefd[0]);
		close(pipefd[1]);
		execlp("ping", "ping", "-c", "5", "google.com", NULL);
	}
	pid2 = fork();
	if (pid2 < 0)
		return (1);

	if (pid2 == 0)
	{
		//child process 2
		dup2(pipefd[0], STDIN_FILENO);
		close(pipefd[0]);
		close(pipefd[1]);
		execlp("grep", "grep", "rtt", NULL);
	}

	close(pipefd[0]);
	close(pipefd[1]);

	waitpid(pid1, NULL, 0);
	waitpid(pid2, NULL, 0);


	return (0);
}
