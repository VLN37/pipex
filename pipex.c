/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jofelipe <jofelipe@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/25 22:17:58 by jofelipe          #+#    #+#             */
/*   Updated: 2021/09/29 04:54:15 by jofelipe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include "libft.h"

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
	if(!validation(argc, envp))
		return (1);
	data.file_in = open(argv[1], O_RDWR);
	data.file_out = open(argv[argc - 1], O_RDWR);
	data.new_argv = alloc_argv(argc, argv);
	data = parser(argc, data.new_argv, envp, data);
	exec(data, envp);
	if (DEBUG)
		debug(data, argc, argv);
	cleanup(data);
}
