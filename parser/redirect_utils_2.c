#include "parser.h"

static char	*quoters_dollar(t_par *par, char *str, int *i)
{
	if (str[*i] == '\'')
	{
		str = ft_one_quoter(str, i);
		(*i)++;
	}
	else if (str[*i] == '\"')
	{
		str = ft_double_quoter(str, i, *par->envp);
		(*i)++;
	}
	else if (str[*i] == '$')
		str = ft_dollar(str, i, *par->envp);
	return (str);
}

static char	*loop(t_par *par, char *str, int *i)
{
	while (str[*i])
	{
		if (str[*i] == '\'' || str[*i] == '\"' || str[*i] == '$')
			str = quoters_dollar(par, str, i);
		else if (str[*i] == '\\')
			str = ft_slash(str, i);
		else if (str[*i] == 9)
			str[*i] = 32;
		else if (str[*i] == 32 && *i > 0)
		{
			if (str[*i - 1] == 32)
				str = input_value_to_string(str, "", 1, *i);
			else
				(*i)++;
		}
		else if (str[*i] == 32 && (*i) == 0)
			str = input_value_to_string(str, "", 1, *i);
		else
			(*i)++;
		if (!str)
			return (str);
	}
	return (str);
}

char	*parser_filename(t_par *par, char *str_orig)
{
	int		j;
	char	*str;

	j = 0;
	if (str_orig[j] == '\'' || str_orig[j] == '\"')
	{
		if (str_orig[j] == '\'' && str_orig[j + 1] == '\'')
		{
			str = ft_strdup("");
			free(str_orig);
			return (str);
		}
		if (str_orig[j] == '\"' && str_orig[j + 1] == '\"')
		{
			str = ft_strdup("");
			free(str_orig);
			return (str);
		}
	}
	str = ft_strdup(str_orig);
	free(str_orig);
	str = loop(par, str, &j);
	return (str);
}
