/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jofelipe <jofelipe@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/25 22:17:58 by jofelipe          #+#    #+#             */
/*   Updated: 2021/11/19 23:14:57 by jofelipe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include "libft.h"

char	**alloc_argv(int argc, char **argv)
{
	int		i;
	char	**new_argv;

	i = -1;
	new_argv = (char **)malloc(sizeof(char *) * argc - 3);
	while (++i < argc - 3)
		new_argv[i] = ft_strdup(argv[i + 2]);
	i = -1;
	while (++i < argc - 3)
		new_argv[i] = ftex_str_replace_all(new_argv[i], OLDPAT, NEWPAT);
	new_argv[i] = NULL;
	return (new_argv);
}

int	main(int argc, char **argv, char **envp)
{
	t_data	data;

	data.file_in = open(argv[1], O_RDONLY, 0777);
	if (data.file_in == -1)
		return (1);
	data.file_out = open(argv[argc - 1], O_RDWR | O_CREAT | O_TRUNC, 0777);
	if (data.file_out == -1)
		return (1);
	if (!validation(argc, envp))
		return (errno);
	data.new_argv = alloc_argv(argc, argv);
	data = parser(argc, data.new_argv, envp, data);
	if (DEBUG == 1)
		debug(data, argc, data.new_argv);
	exec(data, envp);
	cleanup(data, EXIT_SUCCESS);
}
