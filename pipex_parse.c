/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_parse.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jofelipe <jofelipe@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/26 20:55:36 by jofelipe          #+#    #+#             */
/*   Updated: 2021/09/28 03:59:40 by jofelipe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include "libft.h"

static char	***parse_commands(int argc, char **argv, char ***cmds)
{
	int	i;

	i = -1;
	cmds = malloc(sizeof(char **) * argc - 3 + 1);
	while (++i < argc - 3)
		cmds[i] = ft_split(argv[i + 2], ' ');
	cmds[i] = NULL;
	return (cmds);
}

static char	**parse_path(char **envp)
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

static char	*test_access(char **path, char *cmd)
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

//handle errors
static char	**parse_access(char **path, char ***cmd, int cmd_count)
{
	int		i;
	char	**accesspath;

	accesspath = (char **)malloc((cmd_count + 1) * sizeof(char *));
	i = 0;
	while (cmd[i])
	{
		accesspath[i] = test_access(path, cmd[i][0]);
		if (!accesspath[i])
			return (NULL);
		++i;
	}
	accesspath[i] = NULL;
	return (accesspath);
}

t_data	parser(int argc, char **argv, char **envp, t_data data)
{
	data.cmds = parse_commands(argc, argv, data.cmds);
	data.path = parse_path(envp);
	data.accesspath = parse_access(data.path, data.cmds, argc - 3);
	return (data);
}
