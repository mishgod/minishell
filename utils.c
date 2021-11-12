#include "libshell.h"

int	count_args(char **arr)
{
	int	i;

	i = 0;
	while (arr[i] != NULL)
		i++;
	return (i);
}

char	**change_envp(char *name, char *arg, char **arr)
{
	int	i;

	i = 0;
	name = ft_strjoin(name, "=");
	while (arr[i])
	{
		if (!ft_strncmp(arr[i], name, ft_strlen(name)))
		{
			free (arr[i]);
			arr[i] = ft_strjoin(name, arg);
			free (name);
			return (arr);
		}
		i++;
	}
	name = join_strings_with_free_first(name, arg);
	arr = add_line(name, arr);
	free (name);
	return (arr);
}

char	**add_line(char *str, char **arr)
{
	int		i;
	char	**new_arr;

	i = 0;
	while (arr[i])
		i++;
	new_arr = malloc((i + 2) * sizeof(char *));
	new_arr[i + 1] = NULL;
	i = 0;
	while (arr[i])
	{
		new_arr[i] = ft_strdup(arr[i]);
		free (arr[i]);
		i++;
	}
	new_arr[i] = ft_strdup(str);
	free (arr);
	return (new_arr);
}

char	**get_envp(char **arr)
{
	int		i;
	char	**new_arr;

	i = 0;
	while (arr[i])
		i++;
	new_arr = malloc((i + 1) * sizeof(char *));
	new_arr[i] = NULL;
	i = 0;
	while (arr[i])
	{
		new_arr[i] = ft_strdup(arr[i]);
		i++;
	}
	return (new_arr);
}
