/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jofelipe <jofelipe@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/23 00:51:03 by jofelipe          #+#    #+#             */
/*   Updated: 2021/12/02 16:47:22 by jofelipe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H

# ifndef DEBUG
#  define DEBUG 0
# endif
# define OLDPAT " ' '"
# define NEWPAT " [0x69ROFLBRO0x69]"
# define OLDPAT2 " "
# define NEWPAT2 "[0x69ROFLBRO0x69]"

# include <string.h>
# include <errno.h>
# include <fcntl.h>
# include <sys/wait.h>

typedef struct s_data
{
	int		file_in;
	int		file_out;
	int		fd[2];
	int		pid;
	int		heredoc;
	char	**accesspath;
	char	**path;
	char	***cmds;
	char	**new_argv;
	char	*limiter;
}	t_data;

t_data	parser(int argc, char **argv, char **envp, t_data data);
int		validation(int argc, char **envp);
void	debug(t_data data, int argc, char **argv);
void	cleanup(t_data data, int iserror);
void	dup2_errorhandler(int dupvar1, int dupvar2, t_data data);
void	exec(t_data data, char **envp);

#endif
