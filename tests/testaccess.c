#include "pipex.h"
#include "libft.h"
#include <stdio.h>

char **getpath(char **envp)
{
	int	i;
	char **ret;
	i = 0;

	while (envp)
	{
		if (!ft_strncmp(envp[i], "PATH", 4))
		{
			ret = ft_split(envp[i], ':');
			int	j = 0;
			return (ret);
		}
		i++;
	}
	return (NULL);
}

char *getaccess(char **path)
{
	int	i;
	char *bin;

	i = 1;
	while (path[i])
	{
		bin = ft_strjoin(path[i], "/cat");
		if (!access(bin, X_OK))
		{
			if (!ft_strnstr(bin, "polaris", ft_strlen(bin)))
			{
				printf("%s\n", bin);
				return(bin);
			}
		}
		free(bin);
		i++;
	}
	return (NULL);
}

int	main(int argc, char **argv, char **envp)
{
	char **path;
	char *binpath;
	char **argv2;

	argv2 = ft_split("cat", ' ');
	path = getpath(envp);
	getaccess(path);

	int	file_in = open("scores", O_RDONLY);
	dup2(file_in, STDIN_FILENO);
	int pid1 = fork();
	if (pid1 == 0)
	{
		execve(getaccess(path), argv2, envp);
	}
	close(0);
	close(file_in);
	return (0);
}
