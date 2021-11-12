#include "libshell.h"

static char	**shlvl(char **envp)
{
	int		i;
	char	*str;
	char	*itoa;

	i = 0;
	str = return_str_value("SHLVL", envp);
	if (str)
		i = ft_atoi(str);
	if (i > 998)
		change_envp("SHLVL", "", envp);
	else
	{
		itoa = ft_itoa(i + 1);
		envp = change_envp("SHLVL", itoa, envp);
		free(itoa);
	}
	return (envp);
}

static void	minishell(char **envp)
{
	char	*str;

	envp = get_envp(envp);
	envp = shlvl(envp);
	g_errnum = 0;
	while (1)
	{
		rl_catch_signals = 0;
		signal(SIGINT, catch_signal_c);
		signal(SIGQUIT, SIG_IGN);
		str = readline("minishell$ ");
		signal(SIGINT, catch_empty_signal_c);
		if (str == NULL)
		{
			ft_putstr_fd("\e[1A\e[11C" "exit\n", 1);
			break ;
		}
		if (str[0] != 0)
			add_history(str);
		if (str[0])
			ft_parser(str, &envp);
	}
	free_arr(envp);
}

int	main(int argc, char **argv, char *envp[])
{
	if (argc != 1)
	{
		printf("minishell: Invalid arguments\n");
		return (1);
	}
	(void)argv;
	minishell(envp);
	return (g_errnum);
}
