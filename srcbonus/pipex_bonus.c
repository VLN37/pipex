/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jofelipe <jofelipe@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/25 22:17:58 by jofelipe          #+#    #+#             */
/*   Updated: 2021/11/17 19:24:48 by jofelipe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"
#include "libft.h"

void	wrathchild(t_data data, char **envp, int i)
{
	dup2_errorhandler(data.file_in, STDIN_FILENO, data);
	if (!data.cmds[i + 1])
		dup2_errorhandler(data.file_out, STDOUT_FILENO, data);
	else
		dup2_errorhandler(data.fd[1], STDOUT_FILENO, data);
	if (i > 0 || data.heredoc)
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

char	**alloc_argv_heredoc(int argc, char **argv)
{
	int		i;
	char	**new_argv;

	i = -1;
	new_argv = (char **)malloc(sizeof(char *) * (argc - 4));
	while (++i < argc - 4)
		new_argv[i] = ft_strdup(argv[i + 3]);
	i = -1;
	while (++i < argc - 4)
		new_argv[i] = ftex_str_replace_all(new_argv[i], OLDPAT, NEWPAT);
	new_argv[i] = NULL;
	return (new_argv);
}

char	**alloc_argv(int argc, char **argv)
{
	int		i;
	char	**new_argv;

	i = -1;
	new_argv = (char **)malloc(sizeof(char *) * (argc - 3));
	while (++i < argc - 3)
		new_argv[i] = ft_strdup(argv[i + 2]);
	i = -1;
	while (++i < argc - 3)
		new_argv[i] = ftex_str_replace_all(new_argv[i], OLDPAT, NEWPAT);
	new_argv[i] = NULL;
	return (new_argv);
}

void	here_doc_handler(char **argv, t_data *data)
{
	int		fd[2];
	char	*line;
	char	*tmp;

	tmp = NULL;
	line = ft_strdup("");
	data->heredoc = 1;
	data->limiter = ftex_strmerge(ft_strdup(argv[2]), ft_strdup("\n"));
	while (1)
	{
		tmp = get_next_line(STDIN_FILENO);
		if (!ft_strncmp(tmp, data->limiter, ft_strlen(data->limiter)))
		{
			close(0);
			break ;
		}
		else
			line = ftex_strmerge(line, tmp);
	}
	free(tmp);
	pipe(fd);
	ft_putstr_fd(line, fd[1]);
	free(line);
	close(fd[1]);
	data->file_in = fd[0];
}

void	standard_handler(char **argv, t_data *data)
{
	data->heredoc = 0;
	data->file_in = open(argv[1], O_RDWR, 0777);
}

int	main(int argc, char **argv, char **envp)
{
	t_data	data;

	setbuf(stdout, NULL);
	if (!ft_strncmp(argv[1], "here_doc", 8))
	{
		here_doc_handler(argv, &data);
	}
	else
		standard_handler(argv, &data);
	if (data.file_in == -1)
		cleanup(data, errno);
	data.file_out = open(argv[argc - 1], O_RDWR | O_CREAT, 0777);
	if (data.file_out == -1)
		cleanup(data, errno);
	if (!validation(argc, envp))
		return (errno);
	if (data.heredoc)
		data.new_argv = alloc_argv_heredoc(argc, argv);
	else
		data.new_argv = alloc_argv(argc, argv);
	ftex_minprintf("here\n");
	data = parser(argc, data.new_argv, envp, data);
	exec(data, envp);
	if (DEBUG)
		debug(data, argc, argv);
	cleanup(data, EXIT_SUCCESS);
}
