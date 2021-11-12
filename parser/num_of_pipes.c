#include "parser.h"

static int	check_open_pipe(char *str, int last_pipe, int first_pipe)
{
	int	i;
	int	flag_start;

	i = 0;
	flag_start = 0;
	if (first_pipe == -1)
		return (0);
	while (i < first_pipe)
	{
		if (str[i] > 32 && str[i] < 127)
			flag_start = 1;
		i++;
	}
	i = last_pipe;
	while (str[++i])
		if (str[i] > 32 && str[i] < 127 && flag_start)
			return (0);
	return (1);
}

int	check_consecutive_pipes(char *str, int i)
{
	i++;
	while ((str[i] == 32 || str[i] == 9) && str[i])
		i++;
	if (str[i] == '|')
		return (1);
	return (0);
}

static int	met_pipe(t_par *par, char *str, int *i, int pipes[2])
{
	if (check_consecutive_pipes(str, *i))
	{
		printf("minishell: syntax error near unexpected token '|'\n");
		free(str);
		g_errnum = 258;
		return (1);
	}
	if (pipes[0] == -1)
		pipes[0] = *i;
	par->num_of_pipes++;
	pipes[1] = *i;
	(*i)++;
	return (0);
}

int	work_with_str(t_par *par, char *str, int pipes[2])
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\'' || str[i] == '\"')
			skip_quoters(str, &i, str[i]);
		else if (str[i] == '\\')
			i += 2;
		else if (str[i] == 124)
		{
			if (met_pipe(par, str, &i, pipes))
				return (1);
		}
		else
			i++;
	}
	return (0);
}

int	num_of_pipes(t_par *par, char *orig_str)
{
	char	*str;
	int		pipes[2];

	par->num_of_pipes = 0;
	par->current_pipe = 0;
	pipes[0] = -1;
	pipes[1] = -1;
	str = ft_strdup(orig_str);
	if (work_with_str(par, str, pipes))
		return (1);
	if (check_open_pipe(str, pipes[1], pipes[0]))
	{
		printf("minishell: syntax error near unexpected token '|'\n");
		free(str);
		g_errnum = 258;
		return (1);
	}
	free (str);
	return (0);
}
