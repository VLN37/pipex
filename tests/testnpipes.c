/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   testnpipes.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jofelipe <jofelipe@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/26 00:01:37 by jofelipe          #+#    #+#             */
/*   Updated: 2021/09/26 00:47:36 by jofelipe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>

int	main(int argc, char **argv)
{
	int	file_in;
	int	file_out;
	int	pipefd[2];
	int	pid1;
	int	pid2;
	int	pid3;

	pipe(pipefd);
	file_in = open(argv[1], O_RDWR);
	file_out = open(argv[2], O_RDWR);
	dup2(file_in, STDIN_FILENO);
	dup2(file_out, STDOUT_FILENO);

	pid1 = fork();
	if (pid1 == 0)
	{
		dup2(pipefd[1], STDOUT_FILENO);
		close(pipefd[0]);
		close(pipefd[1]);
		execlp("grep", "grep", "reprehen", NULL);
	}
	pid2 = fork();
	if (pid2 == 0)
	{
		dup2(pipefd[0], STDOUT_FILENO);
		dup2(pipefd[1], STDIN_FILENO);
		close(pipefd[0]);
		close(pipefd[1]);
		execlp("grep", "grep", "velit", NULL);
	}
	pid3 = fork();
	if (pid2 == 0)
	{
		dup2(pipefd[0], STDIN_FILENO);
		close(pipefd[0]);
		close(pipefd[1]);
		execlp("tr", "tr", "v", "a", NULL);
	}

	waitpid(pid1, NULL, 0);
	waitpid(pid2, NULL, 0);
	waitpid(pid3, NULL, 0);

	close(pipefd[0]);
	close(pipefd[1]);
	return (0);
}
