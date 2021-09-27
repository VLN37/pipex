/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jofelipe <jofelipe@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/25 22:17:58 by jofelipe          #+#    #+#             */
/*   Updated: 2021/09/26 21:10:59 by jofelipe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include "libft.h"

// cmd1 << <LIMITER> | <cmd2> >> outfile ????????


void	debug(char ***cmds, char **path, char **accesspath)
{
	int	i;
	int	j;
	int	k;
	int	l;

	printf("\n============= PATH =============\n\n");
	j = 0;
	while (path[j])
		printf("%s\n", path[j++]);
	printf("\n============ ACCESS ============\n\n");
	i = -1;
	while (cmds[++i])
		printf("Command: %s\nAccess: %s\n", cmds[i][0], accesspath[i]);
	printf("\n=========== COMMANDS ===========\n\n");
	k = 0;
	l = 0;
	while (cmds[k])
	{
		while (cmds[k][l])
			printf("%s ", cmds[k][l++]);
		k++;
		l = 0;
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

	data.pid = 1;
	data = parser(argc, argv, envp, data);
	if (DEBUG)
		debug(data.cmds, data.path, data.accesspath);
	cleanup(data);
}
