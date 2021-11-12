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

static char	*spaces(char *str, int *i)
{
	if (str[*i + 1] == 0)
		str = input_value_to_string(str, "", 1, *i);
	else if (*i > 0)
	{
		if (str[*i - 1] == 32)
			str = input_value_to_string(str, "", 1, *i);
		else
			(*i)++;
	}
	else if (*i == 0)
		str = input_value_to_string(str, "", 1, *i);
	return (str);
}

char	*parser_one_command(t_par *par, char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\'' || str[i] == '\"' || str[i] == '$')
			str = quoters_dollar(par, str, &i);
		else if (str[i] == '\\')
			str = ft_slash(str, &i);
		else if (str[i] == 9)
			str[i] = 32;
		else if (str[i] == 32)
			str = spaces(str, &i);
		else
			i++;
		if (!str)
			return (str);
	}
	return (str);
}
