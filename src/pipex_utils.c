/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jofelipe <jofelipe@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/29 04:53:04 by jofelipe          #+#    #+#             */
/*   Updated: 2021/12/01 13:01:15 by jofelipe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include "libft.h"

void	dup2_errorhandler(int dupvar1, int dupvar2, t_data data)
{
	if (dup2(dupvar1, dupvar2) == -1)
		cleanup(data, EXIT_FAILURE);
}

void	debug(t_data data, int argc, char **argv)
{
	int	i;
	int	j;

	(void)argc;
	ftex_minprintf("\n============= PATH =============\n\n");
	i = 0;
	while (data.path[i])
		ftex_minprintf("%s\n", data.path[i++]);
	ftex_minprintf("\n============= ARGV =============\n\n");
	i = -1;
	while (argv[++i])
		ftex_minprintf("argv[%d] %s\n", i, argv[i]);
	ftex_minprintf("\n============ ACCESS ============\n\n");
	i = -1;
	while (data.cmds[++i])
		ftex_minprintf("Cm: %s\nAc: %s\n", data.cmds[i][0], data.accesspath[i]);
	ftex_minprintf("\n=========== COMMANDS ===========\n\n");
	i = -1;
	j = -1;
	while (data.cmds[++i])
	{
		while (data.cmds[i][++j])
			ftex_minprintf("|%s|\n", data.cmds[i][j]);
		j = -1;
	}
}

void	free_allocs(t_data data)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (data.cmds[i])
	{
		while (data.cmds[i][j])
			free(data.cmds[i][j++]);
		free(data.cmds[i++]);
		j = 0;
	}
	i = 0;
	while (data.path[i])
		free(data.path[i++]);
	i = 0;
	while (data.accesspath[i])
		free(data.accesspath[i++]);
	i = 0;
	while (data.new_argv[i])
		free(data.new_argv[i++]);
	free(data.new_argv);
	free(data.cmds);
	free(data.path);
	free(data.accesspath);
}

void	cleanup(t_data data, int iserror)
{
	free_allocs(data);
	if (iserror)
	{
		ft_putstr_fd(strerror(iserror), 2);
		ft_putstr_fd("\n", 2);
		exit(iserror);
	}
	exit(EXIT_SUCCESS);
}
