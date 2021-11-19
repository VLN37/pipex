/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_exec.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jofelipe <jofelipe@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/17 20:00:45 by jofelipe          #+#    #+#             */
/*   Updated: 2021/11/19 17:24:05 by jofelipe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include "libft.h"

void	wrathchild(t_data data, char **envp, int i)
{
	dup2_errorhandler(data.file_in, STDIN_FILENO, data);
	if (!data.cmds[i + 1])
		dup2_errorhandler(data.file_out, STDOUT_FILENO, data);
	else
		dup2_errorhandler(data.fd[1], STDOUT_FILENO, data);
	close(data.fd[0]);
	if (execve(data.accesspath[i], data.cmds[i], envp) == -1)
		cleanup(data, errno);
}

void	exec(t_data data, char **envp)
{
	int	i;

	i = 0;
	while (data.cmds[i])
	{
		pipe(data.fd);
		data.pid = fork();
		if (data.pid == -1)
			cleanup(data, errno);
		else if (data.pid == 0)
			wrathchild(data, envp, i);
		else
		{
			wait(NULL);
			close(data.fd[1]);
			data.file_in = data.fd[0];
			i++;
		}
	}
}
