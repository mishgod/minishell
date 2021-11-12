#include "../libshell.h"
#include "../parser/parser.h"

void	cmd_echo(char **arr)
{
	int	flag;
	int	i;
	int	count;

	count = count_args(arr) - 1;
	i = 1;
	flag = 0;
	while (!ft_strncmp(arr[i], "-n", 2))
	{
		flag = 1;
		i++;
	}
	while (count > 0 && arr[i])
	{
		if (count > i && ft_strncmp(arr[i], "", 1))
			printf("%s ", arr[i]);
		else
			printf("%s", arr[i]);
		i++;
	}
	if (!flag)
		printf("\n");
	exit (errno);
}

char	**cmd_pwd(char **envp, t_par *par)
{
	char	str[500];

	envp = change_envp("_", "pwd", envp);
	if (getcwd(str, 500) != NULL)
	{
		redirect(str, par);
		g_errnum = 0;
	}
	else if (return_str_value("PWD", envp))
	{
		redirect(return_str_value("PWD", envp), par);
		g_errnum = 0;
	}
	else
	{
		printf("minishell: %s\n", strerror(errno));
		g_errnum = 1;
	}
	return (envp);
}

char	**cmd_env(char **envp, t_par *par)
{
	int	i;
	int	pid;
	int	status;

	i = 0;
	envp = change_envp("_", "env", envp);
	pid = fork();
	if (pid == 0)
	{
		dup_fd(par);
		while (envp[i] != NULL)
		{
			if (ft_strrchr(envp[i], '='))
				printf("%s\n", envp[i]);
			i++;
		}
		exit (0);
	}
	waitpid(pid, &status, 0);
	status = WSTOPSIG(status);
	g_errnum = status;
	return (envp);
}

char	**cmd_unset(char **arr, char **envp)
{
	int	i;
	int	j;

	j = count_args(arr);
	envp = change_envp("_", "unset", envp);
	if (j == 1)
		return (envp);
	j--;
	while (j > 0)
	{
		i = 0;
		while (envp[i])
		{
			if (cmp_names(arr[j], envp[i]))
				return (del_line(envp, i));
			i++;
		}
		j--;
	}
	return (envp);
}
