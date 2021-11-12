#include "../libshell.h"
#include "../parser/parser.h"

static char	**cd_home(char str[500], char ***envp)
{
	char	*pwd;

	pwd = return_str_value("HOME", *envp);
	if (!pwd)
	{
		printf("minishell: cd: HOME not set\n");
		g_errnum = 1;
		return (*envp);
	}
	if (chdir(pwd) != -1)
	{
		*envp = change_envp("OLDPWD", return_str_value("PWD", *envp), *envp);
		*envp = change_envp("PWD", getcwd(str, 500), *envp);
	}
	return (*envp);
}

static char	**cd_pt2(char str[500], char **envp)
{
	char	*pwd;

	pwd = return_str_value("OLDPWD", envp);
	if (pwd)
	{
		getcwd(str, 500);
		if (chdir(pwd) != -1)
		{
			envp = change_envp("OLDPWD", str, envp);
			envp = change_envp("PWD", getcwd(str, 500), envp);
			printf("%s\n", str);
		}
	}
	return (envp);
}

static int	cd_dot_dot(char **arr, char ***envp)
{
	char	*str;
	char	pwd[500];
	int		i;

	if (ft_strncmp(arr[1], "..", 3))
		return (0);
	str = return_str_value("PWD", *envp);
	if (!str)
		return (0);
	i = ft_strlen(str) - 1;
	if (i < 2)
		return (1);
	while (str[i] && str[i] != '/')
		i--;
	str = ft_substr(str, 0, i);
	if (chdir(str) != -1)
	{
		*envp = change_envp("OLDPWD", str, *envp);
		free (str);
		*envp = change_envp("PWD", getcwd(pwd, 500), *envp);
		return (1);
	}
	free (str);
	return (0);
}

char	**cmd_cd(char **arr, char **envp)
{
	char	str[500];
	int		flag;

	flag = 0;
	envp = change_envp("_", "cd", envp);
	if (count_args(arr) == 1)
		return (cd_home(str, &envp));
	if (cd_dot_dot(arr, &envp))
		return (envp);
	if (arr[1])
		if (ft_strlen(arr[1]) == 1 && arr[1][0] == '-')
			return (cd_pt2(str, envp));
	if (getcwd(str, 500))
		flag = 1;
	if (chdir(arr[1]) != -1 && flag == 1)
		envp = change_envp("OLDPWD", str, envp);
	else if (chdir(arr[1]) == -1)
	{
		printf("minishell: cd: %s\n", strerror(errno));
		g_errnum = 1;
	}
	if (getcwd(str, 500))
		envp = change_envp("PWD", getcwd(str, 500), envp);
	return (envp);
}
