#include "../parser/parser.h"

int	check_numerics(char *str)
{
	long long	i;
	int			flag;
	int			flag_minus;

	i = -1;
	flag = 0;
	flag_minus = 0;
	while (str[++i])
	{
		if ((str[i] > 47 && str[i] < 58) || str[i] == 32 || str[i] == 9
			|| str[i] == 45 || str[i] == 43)
		{
			if (str[i] > 47 && str[i] < 58)
				flag++;
			if (str[i] == '-')
				flag_minus++;
		}
		else
			return (1);
	}
	if (flag)
		return (0);
	return (1);
}

static int	ft_exit(t_par *par)
{
	if (par->arg[1])
	{
		if (par->arg[2])
		{
			printf("minishell: exit: too many arguments\n");
			g_errnum = 1;
			return (1);
		}
		if (check_numerics(par->arg[1]))
		{
			printf("minishell: exit: %s: numeric argument required\n",
				   par->arg[1]);
			par->errno_exit = 255;
		}
		else
		{
			par->errno_exit = ft_atoi(par->arg[1]);
			if (par->errno_exit > 0)
				par->errno_exit = par->errno_exit % 256;
			else
				while (par->errno_exit < 0)
					par->errno_exit += 256;
		}
	}
	exit (par->errno_exit);
}

void	ft_exec_command(t_par *par)
{
	char	**envp;

	envp = *par->envp;
	if (!ft_strncmp(par->arg[0], "echo", 5))
		cmd_echo(par->arg);
	else if (!ft_strncmp(par->arg[0], "cd", 3))
		envp = cmd_cd(par->arg, envp);
	else if (!ft_strncmp(par->arg[0], "pwd", 4))
		envp = cmd_pwd(envp, par);
	else if (!ft_strncmp(par->arg[0], "export", 7))
		envp = cmd_export(par->arg, envp, par);
	else if (!ft_strncmp(par->arg[0], "env", 4))
		envp = cmd_env(envp, par);
	else if (!ft_strncmp(par->arg[0], "unset", 6))
		envp = cmd_unset(par->arg, envp);
	else if (!ft_strncmp(par->arg[0], "exit", 5))
	{
		printf("exit\n");
		if (ft_exit(par))
			return ;
	}
	else
		cmd_other(par->arg, envp);
	*par->envp = envp;
}
