/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jofelipe <jofelipe@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/23 00:51:03 by jofelipe          #+#    #+#             */
/*   Updated: 2021/09/26 21:00:14 by jofelipe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# ifndef DEBUG
#  define DEBUG 0
# endif

# include <stdio.h>

# include <unistd.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <stdlib.h>

typedef struct s_data
{
	int		file_in;
	int		file_out;
	int		pipefd[2];
	int		pid;
	char	**accesspath;
	char	**path;
	char	***cmds;
}	t_data;

t_data parser(int argc, char **argv, char **envp, t_data data);

#endif
