#include "pipex.h"
#include "libft.h"
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <stdio.h>

char **command_parse(char *cmd)
{
	int	i;
	char **ret;
	i = 0;

	ret = ft_split(cmd, ' ');
	while (ret[i])
		printf("%s\n", ret[i++]);
	return (ret);
}

int	main(int argc, char **argv, char **envp)
{
	int	file_in;
	int	file_out;
	int	pipefd[2];
	int	pid1;
	int	pid2;
	char *path;
	char **cmd1;
	char **cmd2;
	int i = 0;

	cmd1 = command_parse(argv[2]);
	path = "/usr/bin/";
	pipe(pipefd);
	file_in = open(argv[1], O_RDWR);
	// file_out = open(argv[2], O_RDWR);
	dup2(file_in, STDIN_FILENO);
	// dup2(file_out, STDOUT_FILENO);

	pid1 = fork();
	if (pid1 == 0)
	{
		//dup2(pipefd[1], STDOUT_FILENO);
		close(pipefd[0]);
		close(pipefd[1]);
		execve(ft_strjoin(path, cmd1[0]), cmd1, envp);
	}
	// pid2 = fork();
	// if (pid2 == 0)
	// {
	// 	dup2(pipefd[0], STDIN_FILENO);
	// 	close(pipefd[0]);
	// 	close(pipefd[1]);
	// 	execlp("tr", "tr", "\n", " ", NULL);
	// }

	close(pipefd[0]);
	close(pipefd[1]);
	waitpid(pid1, NULL, 0);
	// waitpid(pid2, NULL, 0);

	return (0);
}
