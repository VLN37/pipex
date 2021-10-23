/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jofelipe <jofelipe@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/29 04:53:04 by jofelipe          #+#    #+#             */
/*   Updated: 2021/10/23 11:11:14 by jofelipe         ###   ########.fr       */
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
	if (iserror)
	{
		ft_putstr_fd(strerror(iserror), 2);
		ft_putstr_fd("\n", 2);
		exit(iserror);
	}
	free_allocs(data);
	exit(EXIT_SUCCESS);
}
