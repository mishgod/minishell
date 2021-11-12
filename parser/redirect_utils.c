#include "parser.h"

void	error_open(char **str, char *file_name)
{
	printf("minishell: %s: %s\n", file_name, strerror(errno));
	g_errnum = 1;
	free(*str);
	*str = NULL;
}

static void	quoters(t_par *par, char *str, int *i)
{
	if (str[*i] == '\'')
	{
		(*i)++;
		while (str[*i] != '\'')
			(*i)++;
	}
	if (str[*i] == '\"')
	{
		(*i)++;
		while (str[*i] != '\"')
		{
			if (str[*i] == '$')
			{
				str = ft_dollar(str, i, *par->envp);
				(*i)--;
			}
			(*i)++;
		}
	}
}

int	before_filename(t_par *par, char *str, int *i)
{
	while (str[*i] > 32 && str[*i] < 127)
	{
		if (str[*i] == '<' || str[*i] == '>')
		{
			printf("minishell: syntax error near unexpected token '%c'\n", \
			str[*i - 1]);
			g_errnum = 258;
			free(str);
			str = NULL;
			return (1);
		}
		quoters(par, str, i);
		(*i)++;
	}
	return (0);
}

int	check_in_redirect(t_par *par, char *str, int *i, char *token)
{
	int	k;

	if (!str[*i])
	{
		printf("minishell: syntax error near unexpected token '%s'\n", token);
		g_errnum = 258;
		free(str);
		str = NULL;
		return (-1);
	}
	while (str[*i] == 9 || str[*i] == 32)
		(*i)++;
	k = *i;
	if (!str[*i])
	{
		printf("minishell: syntax error near unexpected token '%s'\n", token);
		g_errnum = 258;
		free(str);
		str = NULL;
		return (-1);
	}
	if (before_filename(par, str, i))
		return (-1);
	return (k);
}
