/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jofelipe <jofelipe@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/25 22:17:58 by jofelipe          #+#    #+#             */
/*   Updated: 2021/09/28 09:29:36 by jofelipe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include "libft.h"

void	debug(char ***cmds, char **path, char **accesspath)
{
	int	i;
	int	j;

	printf("\n============= PATH =============\n\n");
	i = 0;
	while (path[i])
		printf("%s\n", path[i++]);
	printf("\n============ ACCESS ============\n\n");
	i = -1;
	while (cmds[++i])
		printf("Command: %s\nAccess: %s\n", cmds[i][0], accesspath[i]);
	printf("\n=========== COMMANDS ===========\n\n");
	i = 0;
	j = 0;
	while (cmds[i])
	{
		while (cmds[i][j])
			printf("%s ", cmds[i][j++]);
		i++;
		j = 0;
		printf("\n");
	}
}

void cleanup(t_data data)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (data.cmds[i])
	{
		while(data.cmds[i][j])
			free(data.cmds[i][j++]);
		free(data.cmds[i]);
		++i;
		j = 0;
	}
	i = 0;
	while (data.path[i])
		free(data.path[i++]);
	i = 0;
	while (data.accesspath[i])
		free(data.accesspath[i++]);
	free(data.cmds);
	free(data.path);
	free(data.accesspath);
}

int	main(int argc, char **argv, char **envp)
{
	t_data	data;

	setbuf(stdout, NULL);
	int j = -1;
	while (++j < argc)
		printf("argv[%d] %s\n", j, argv[j]);
	data.file_in = open(argv[1], O_RDWR);
	data.file_out = open(argv[argc - 1], O_RDWR);
	data = parser(argc, argv, envp, data);
	int	i = 0;
	while (data.cmds[i])
	{
		pipe(data.fd);
		data.pid = fork();
		if (data.pid == 0)
		{
			dup2(data.file_in, STDIN_FILENO);
			if (!data.cmds[i + 1])
				dup2(data.file_out, STDOUT_FILENO);
			else
				dup2(data.fd[1], STDOUT_FILENO);
			if (i > 0)
				close(data.fd[0]);
			execve(data.accesspath[i], data.cmds[i], envp);
		}
		else
		{
			wait(NULL);
			close(data.fd[1]);
			data.file_in = data.fd[0];
			i++;
		}
	}
	if (DEBUG)
		debug(data.cmds, data.path, data.accesspath);
	cleanup(data);
}

	// pipe(data.fd);
	// dup2(data.file_in, STDIN_FILENO);
	// dup2(data.file_out, STDOUT_FILENO);
	// int i = 0;
	// data.pid = fork();
	// dprintf(2, "%d\n", data.pid);
	// if (data.pid == 0)
	// {
	// 	// dprintf(2, "%d\n", data.pid);
	// 	dup2(data.fd[1], STDOUT_FILENO);
	// 	close(data.fd[0]);
	// 	close(data.fd[1]);
	// 	dprintf(2, "access: %s cmd: %s\n", data.accesspath[i], data.cmds[i][0]);
	// 	execve(data.accesspath[i], data.cmds[i], envp);
	// 	waitpid(data.pid, NULL, 0);
	// }
	// //  dprintf(2, "%d\n", data.pid);
	// ++i;
	// data.pid = fork();
	// if (data.pid == 0)
	// {
	// 	dup2(data.fd[0], STDIN_FILENO);
	// 	close(data.fd[0]);
	// 	close(data.fd[1]);
	// 	dprintf(2, "access: %s cmd: %s\n", data.accesspath[i], data.cmds[i][0]);
	// 	execve(data.accesspath[i], data.cmds[i], envp);
	// 	waitpid(data.pid, NULL, 0);
	// }
	// close(data.fd[0]);
	// close(data.fd[1]);
