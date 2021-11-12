#include "../libshell.h"
#include "sys/stat.h"

static char	*get_path_piece(char *str)
{
	char	*path;
	int		i;

	i = 0;
	while (str[i] && str[i] != ':')
		i++;
	path = ft_calloc(i + 1, sizeof(char));
	path = ft_memcpy(path, str, i);
	return (path);
}

static void	run_cmd(char *path, char **arr, char **envp)
{
	if (execve(path, arr, envp) == -1)
	{
		printf("minishell: %s: Permission denied\n", arr[0]);
		g_errnum = 126;
	}
	g_errnum = 0;
	exit(g_errnum);
}

static char	*get_path(char *str, char *arr)
{
	int	i;

	i = ft_strlen(str) - 1;
	if (arr[0] == '/')
		return (ft_strdup(arr));
	if (arr[0] != '.' && !ft_strrchr(arr, '/'))
		return (NULL);
	if (arr[0] != '.')
		return (join_strings_with_free_first(ft_strjoin(str, "/"), arr));
	if (arr[1] == '/')
		return (ft_strjoin(str, arr + 1));
	while (str[i] && str[i] != '/')
		i--;
	while (str[i])
	{
		str[i] = '\0';
		i++;
	}
	return (ft_strjoin(str, arr + 2));
}

int	cmd_other_2(char **arr, char **envp, char *str)
{
	struct stat	sb;
	char		*path;

	while (*str)
	{
		if (*str == ':')
			str++;
		path = get_path_piece(str);
		str = str + ft_strlen(path);
		path = join_strings_with_free_first(path, "/");
		path = join_strings_with_free_first(path, arr[0]);
		sb.st_mode = 0;
		if (stat(path, &sb) != -1)
		{
			if (S_ISREG(sb.st_mode) != 0)
			{
				run_cmd(path, arr, envp);
				return (1);
			}
		}
		free (path);
	}
	return (0);
}

void	cmd_other(char **arr, char **envp)
{
	char		str[500];
	char		*pwd;
	struct stat	sb;

	pwd = getcwd(str, 500);
	pwd = get_path(pwd, *arr);
	if (stat(pwd, &sb) != -1)
	{
		if (S_ISREG(sb.st_mode) != 0)
		{
			run_cmd(pwd, arr, envp);
			free(pwd);
			return ;
		}
	}
	pwd = return_str_value("PATH", envp);
	if (pwd != NULL)
		if (cmd_other_2(arr, envp, pwd))
			return ;
	printf("minishell: %s: command not found\n", arr[0]);
	errno = 127;
}
