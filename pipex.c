/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jofelipe <jofelipe@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/25 22:17:58 by jofelipe          #+#    #+#             */
/*   Updated: 2021/09/26 16:38:37 by jofelipe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include "libft.h"

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

char **parse_path(char **envp)
{
	int	i;
	char **ret;
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

int	main(int argc, char **argv, char **envp)
{
	t_data	data;

	data.cmds = parse_commands(argc, argv, data.cmds);
	data.path = parse_path(envp);
	if (!data.path)
		return (1);

}
