#include "../libshell.h"
#include "../parser/parser.h"

static void	print_pt2(char **envp)
{
	int	i;
	int	j;

	i = 0;
	while (envp[i] != NULL)
	{
		j = 0;
		if (ft_strrchr(envp[i], '='))
		{
			while (envp[i][j] != '=')
				j++;
			write(1, "declare -x ", 11);
			write(1, envp[i], j);
			printf("=\"%s\"\n", envp[i] + j + 1);
		}
		else
			printf("declare -x %s\n", envp[i]);
		free(envp[i]);
		i++;
	}
	free(envp);
	exit (0);
}

static void	print_sorted_envp(char **envp, t_par *par)
{
	int	pid;
	int	status;

	pid = fork();
	if (pid == 0)
	{
		dup_fd(par);
		print_pt2(envp);
	}
	waitpid(pid, &status, 0);
	free_arr(envp);
	status = WSTOPSIG(status);
	g_errnum = status;
}

static int	envp_str_cmp(char *str, char *str2)
{
	int	i;

	i = 0;
	while (str[i] && str2[i])
	{
		if (str[i] != str2[i])
			return (str[i] - str2[i]);
		if (str[i] == '=')
			return (1);
		if (str2[i] == '=')
			return (-1);
		i++;
	}
	return (str[i] - str2[i]);
}

static void	sort_envp(char **envp, t_par *par)
{
	char	*str;
	int		i;
	int		j;

	i = 0;
	while (envp[i++])
		if (cmp_names("_", envp[i - 1]))
			envp = del_line(envp, i - 1);
	i = count_args(envp) - 1;
	while (i--)
	{
		j = 0;
		while (j < i + 1)
		{
			if (envp_str_cmp(envp[j], envp[j + 1]) > 0)
			{
				str = envp[j];
				envp[j] = envp[j + 1];
				envp[j + 1] = str;
			}
			j++;
		}
	}
	print_sorted_envp(envp, par);
}

char	**cmd_export(char **arr, char **envp, t_par *par)
{
	int	i;

	i = 1;
	envp = change_envp("_", "export", envp);
	if (count_args(arr) == 1 || arr[1][0] == 35)
	{
		sort_envp(get_envp(envp), par);
		return (envp);
	}
	while (arr[i])
	{
		if (ft_strrchr(arr[i], 35) || ft_strrchr(arr[i], 37)
			|| ft_strrchr(arr[i], 94) || export_dst(arr[i]))
		{
			printf("minishell$ export: `%s': not a valid identifier\n", arr[i]);
			g_errnum = 1;
			return (envp);
		}
		envp = change_envp2(arr[i], envp);
		i++;
	}
	return (envp);
}
