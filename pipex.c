/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jofelipe <jofelipe@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/25 22:17:58 by jofelipe          #+#    #+#             */
/*   Updated: 2021/09/29 02:58:32 by jofelipe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include "libft.h"

void	debug(t_data data, int argc, char **argv)
{
	int	i;
	int	j;

	printf("\n============= PATH =============\n\n");
	i = 0;
	while (data.path[i])
		printf("%s\n", data.path[i++]);
	printf("\n============= ARGV =============\n\n");
	i = 0;
	while (++i < argc)
		printf("argv[%d] %s\n", i, argv[i]);
	printf("\n============ ACCESS ============\n\n");
	i = -1;
	while (data.cmds[++i])
		printf("Cmd: %s\nAccess: %s\n", data.cmds[i][0], data.accesspath[i]);
	printf("\n=========== COMMANDS ===========\n\n");
	i = 0;
	j = 0;
	while (data.cmds[i])
	{
		while (data.cmds[i][j])
			printf("%s\n", data.cmds[i][j++]);
		i++;
		j = 0;
	}
}

void	cleanup(t_data data)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (data.cmds[i])
	{
		while (data.cmds[i][j])
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

void	exec(t_data data, char **envp)
{
	int	i;

	i = 0;
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
			wait(NULL);
			close(data.fd[1]);
			data.file_in = data.fd[0];
			i++;
	}
}

char **alloc_argv(int argc, char **argv)
{
	int	i;
	int	j;
	char **new_argv;

	i = -1;
	j = -1;
	new_argv = (char **)malloc(sizeof(char *) * argc - 3);
	while(++i < argc - 3)
		new_argv[i] = ft_strdup(argv[i + 2]);
	i = -1;
	while(++i < argc - 3)
		new_argv[i] = str_replace_all(new_argv[i], OLDPAT, NEWPAT);
	return (new_argv);
}

int	main(int argc, char **argv, char **envp)
{
	t_data	data;

	setbuf(stdout, NULL);
	data.file_in = open(argv[1], O_RDWR);
	data.file_out = open(argv[argc - 1], O_RDWR);
	data.new_argv = alloc_argv(argc, argv);
	data = parser(argc, data.new_argv, envp, data);
	exec(data, envp);
	if (DEBUG)
		debug(data, argc, argv);
	cleanup(data);
}
