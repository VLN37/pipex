/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_exec.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jofelipe <jofelipe@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/17 20:00:45 by jofelipe          #+#    #+#             */
/*   Updated: 2021/12/05 11:34:10 by jofelipe         ###   ########.fr       */
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
	{
		ft_putendl_fd(strerror(errno), 2);
		cleanup(data, errno);
	}
}

int	exec(t_data data, char **envp)
{
	int	i;
	int	exit_code;

	i = 0;
	exit_code = 0;
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
			waitpid(data.pid, &exit_code, WNOHANG);
			exit_code = WEXITSTATUS(exit_code);
			close(data.fd[1]);
			data.file_in = data.fd[0];
			i++;
		}
	}
	return (exit_code);
}
