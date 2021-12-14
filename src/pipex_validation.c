/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_validation.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jofelipe <jofelipe@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/29 04:49:12 by jofelipe          #+#    #+#             */
/*   Updated: 2021/12/14 02:06:50 by jofelipe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include "libft.h"

static int	validate_envp(char **envp)
{
	int	i;

	i = 0;
	if (!envp)
		return (0);
	while (envp[i])
	{
		if (!ft_strncmp(envp[i++], "PATH", 4))
			return (1);
	}
	return (0);
}

int	validation(int argc, char **envp)
{
	if (argc < 5)
	{
		ft_putstr_fd("Usage: ./pipex <file1> <cmd1> ... <cmdx> <file2>\n", 2);
		return (0);
	}
	if (!validate_envp(envp))
	{
		ft_putstr_fd("Path not found\n", 2);
		return (0);
	}
	return (1);
}
