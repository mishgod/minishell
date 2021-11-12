#include "parser.h"

static char	*ft_error_key(char *str, int *i)
{
	char	*num;

	(*i)--;
	str = input_value_to_string(str, "", 1, *i);
	num = ft_itoa(g_errnum);
	str = input_value_to_string(str, num, ft_strlen(num), *i);
	*i += ft_strlen(num);
	free (num);
	return (str);
}

static char	*ft_key_exist(char *str, int *i, int begin, char *envp[])
{
	int		len;
	int		j;
	char	*str_key;
	char	*str_var;

	j = begin + 1;
	str_key = ft_substr(str, j, *i - j);
	j = -1;
	len = ft_strlen(str_key);
	str_var = NULL;
	while (envp[++j])
	{
		if (!ft_strncmp(str_key, envp[j], len))
			if (envp[j][len] == '=')
				str_var = take_value_from_key(envp[j], len + 1);
	}
	if (!str_var)
		str_var = ft_strdup("");
	free(str_key);
	str = input_value_to_string(str, str_var, len + 1, begin);
	*i = begin + ft_strlen(str_var);
	free(str_var);
	return (str);
}

static char	*check_character(char *str, int *i)
{
	if (str[(*i)] == '$')
	{
		(*i)++;
		return (str);
	}
	if (str[*i] == '?')
	{
		str = ft_error_key(str, i);
		return (str);
	}
	if (str[*i] == '\\')
		str = ft_slash(str, i);
	return (str);
}

static void	move_pointer(char *str, int *i, int j)
{
	if (ft_isdigit(str[j]))
	{
		while (str[++(*i)])
			if (!ft_isdigit(str[*i]) && !(str[*i] == '_'))
				break ;
	}
	else
	{
		while (str[++(*i)])
			if (!ft_isalnum(str[*i]) && !(str[*i] == '_'))
				break ;
	}
}

char	*ft_dollar(char *str, int *i, char *envp[])
{
	int	j;
	int	begin;

	begin = *i;
	j = *i + 1;
	if (!str[j])
	{
		(*i)++;
		return (str);
	}
	move_pointer(str, i, j);
	if (j != *i)
	{
		str = ft_key_exist(str, i, begin, envp);
		return (str);
	}
	if (str[(*i)] == '$' || str[(*i)] == '?' || str[(*i)] == '\\')
		str = check_character(str, i);
	return (str);
}
