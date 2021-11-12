#include "parser.h"

static int	get_num_of_pipe_or_null(char *str)
{
	int	k;

	k = 0;
	while (str[k] && str[k] != 124)
	{
		if (str[k] == '\"' || str[k] == '\'')
			skip_quoters(str, &k, str[k]);
		else if (str[k] == '\\')
			k += 2;
		else if (str[k] == 124)
			return (k);
		else
			k++;
	}
	return (k);
}

int	check_char(char *str, char c, int *i)
{
	int	flag;

	flag = 0;
	(*i)++;
	if (str[*i] == c)
	{
		(*i)++;
		flag++;
	}
	while ((str[*i] == 9 || str[*i] == 32) && str[*i])
		(*i)++;
	if (!str[*i] || str[*i] == '<' || str[*i] == '>')
	{
		if (flag)
			printf("minishell: syntax error near unexpected token '%c%c'\n", \
			c, c);
		else
			printf("minishell: syntax error near unexpected token '%c'\n", c);
		g_errnum = 258;
		free(str);
		return (1);
	}
	return (0);
}

int	check_open_d_redir_r(char *str_orig)
{
	int		i;
	char	*str;

	str = ft_strdup(str_orig);
	i = 0;
	while (str[i])
	{
		if (str[i] == '\'' || str[i] == '\"')
			skip_quoters(str, &i, str[i]);
		else if (str[i] == '\\')
			i += 2;
		else if (str[i] == '<' || str[i] == '>')
		{
			if (check_char(str, str[i], &i))
				return (1);
		}
		else
			i++;
	}
	free (str);
	return (0);
}

char	*get_one_command(t_par *par, char *str, char **new_str)
{
	int		k;
	char	*one_command;

	k = get_num_of_pipe_or_null(str);
	if (str[k] == 124)
	{
		par->flag.pipe++;
		par->current_pipe++;
		*new_str = ft_substr(str, k + 1, ft_strlen(str) - k - 1);
		one_command = ft_substr(str, 0, k);
		free(str);
		str = one_command;
	}
	else
		*new_str = ft_strdup("");
	if (check_open_d_redir_r(str))
	{
		free(str);
		return (NULL);
	}
	return (str);
}
