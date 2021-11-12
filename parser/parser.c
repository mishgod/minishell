#include "parser.h"

char	*ft_slash(char *str, int *i)
{
	char	*tmp1;
	char	*tmp2;

	tmp1 = ft_substr(str, 0, *i);
	tmp2 = ft_substr(str, *i + 1, ft_strlen(str) - *i);
	free (str);
	str = ft_strjoin(tmp1, tmp2);
	free (tmp1);
	free (tmp2);
	(*i)++;
	return (str);
}

int	check_only_space_line(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		while ((str[i] == 32 || str[i] == 9) && str[i])
			i++;
		if (str[i])
			return (0);
	}
	free (str);
	return (1);
}

static int	main_loop(t_par *par, char **str, char **new_str, int i)
{
	while (*str[i])
	{
		if (par->arg)
			free_arr(par->arg);
		initial_variables(par, new_str);
		*str = get_one_command(par, *str, new_str);
		if (!(*str))
			return (close_and_free(par, *new_str));
		*str = remove_redirects(par, *str);
		if (!(*str))
			return (close_and_free(par, *new_str));
		if (check_only_space_line(*str))
			return (close_and_free(par, *new_str));
		par->arg = new_split(par, *str);
		if (!par->arg)
			return (close_and_free(par, *new_str));
		if (par->flag.pipe)
			ft_pipe(par);
		*str = *new_str;
		i = 0;
	}
	return (0);
}

static int	prep_to_loop(t_par *par, char *str, char **new_str, char **envp[])
{
	par->envp = envp;
	initial_variables(par, new_str);
	if (ft_preparsing(str))
		return (free_str_par(par, str));
	if (num_of_pipes(par, str))
		return (free_str_par(par, str));
	if (ft_pipe_to_fd(par))
		return (free_str_par(par, str));
	return (0);
}

int	ft_parser(char *str, char **envp[])
{
	t_par	*par;
	char	*new_str;

	par = malloc(sizeof(t_par));
	par->errno_exit = g_errnum;
	if (prep_to_loop(par, str, &new_str, envp))
		return (1);
	if (main_loop(par, &str, &new_str, 0))
		return (1);
	g_errnum = 0;
	last_command(par);
	*envp = *par->envp;
	if (par->arg)
		free_arr(par->arg);
	free_str_par(par, str);
	return (0);
}
