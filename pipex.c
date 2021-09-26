/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jofelipe <jofelipe@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/25 22:17:58 by jofelipe          #+#    #+#             */
/*   Updated: 2021/09/26 20:18:41 by jofelipe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include "libft.h"

// cmd1 << <LIMITER> | <cmd2> >> outfile ????????
char	***parse_commands(int argc, char **argv, char ***cmds)
{
	int	i;

	i = -1;
	cmds = malloc(sizeof(char **) * argc - 3 + 1);
	while (++i < argc - 3)
		cmds[i] = ft_split(argv[i + 2], ' ');
	cmds[i] = NULL;
	return (cmds);
}

char	**parse_path(char **envp)
{
	int		i;
	char	**ret;

	i = 0;
	while (envp)
	{
		if (!ft_strncmp(envp[i], "PATH", 4))
		{
			ret = ft_split(envp[i], ':');
			return (ret);
		}
		i++;
	}
	return (NULL);
}

char	*test_access(char **path, char *cmd)
{
	int		i;
	char	*bin;
	char	*cmd2;

	i = 1;
	while (path[i])
	{
		cmd2 = ft_strjoin("/", cmd);
		bin = ft_strjoin(path[i++], cmd2);
		free(cmd2);
		if (!access(bin, X_OK))
			return (bin);
		else
			free(bin);
	}
	return (NULL);
}

char	**parse_access(char **path, char ***cmd, int cmd_count)
{
	int		i;
	int		j;
	char	**accesspath;
	char	*bin;

	accesspath = (char **)malloc((cmd_count + 1) * sizeof(char *));
	i = 0;
	j = 0;
	while (cmd[i])
	{
		accesspath[i] = test_access(path, cmd[i][0]);
		if (!accesspath[i])
			return (NULL); //handle errors
		++i;
	}
	accesspath[i] = NULL;
	return (accesspath);
}

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

	data.cmds = parse_commands(argc, argv, data.cmds);
	data.path = parse_path(envp);
	data.accesspath = parse_access(data.path, data.cmds, argc - 3);
	if (DEBUG)
		debug(data.cmds, data.path, data.accesspath);
	cleanup(data);
}
