#include "parser.h"
#include "../lib/libft.h"
#include "../libshell.h"

char	*take_value_from_key(char *str, int i)
{
	char	*str_var;

	str_var = ft_substr(str, i, ft_strlen(str) - i);
	return (str_var);
}

void	skip_quoters(char *str, int *i, char ch)
{
	(*i)++;
	if (str[*i] == '\"')
	{
		while (str[*i] != ch && str[*i - 1] != '\\' && str[*i])
			(*i)++;
	}
	else
	{
		while (str[*i] != ch && str[*i])
			(*i)++;
	}
	(*i)++;
}

static char	*ft_get_str(char *str, int *i, int j)
{
	char	*tmp1;
	char	*tmp2;
	char	*tmp3;

	tmp1 = ft_substr(str, 0, j);
	tmp2 = ft_substr(str, j + 1, *i - j - 1);
	tmp3 = ft_strjoin(tmp1, tmp2);
	free(tmp1);
	free(tmp2);
	tmp1 = ft_substr(str, *i + 1, ft_strlen(str) - j);
	tmp2 = ft_strjoin(tmp3, tmp1);
	free(tmp1);
	free (tmp3);
	free (str);
	(*i)--;
	(*i)--;
	return (tmp2);
}

char	*ft_double_quoter(char *str, int *i, char *envp[])
{
	int	j;

	j = *i;
	(*i)++;
	while (str[*i] != '\"')
	{
		if (str[*i] == '$')
			str = ft_dollar(str, i, envp);
		else if (str[*i] == '\\' && str[*i + 1] == '\"')
			str = ft_slash(str, i);
		else
			(*i)++;
	}
	str = ft_get_str(str, i, j);
	return (str);
}

char	*ft_one_quoter(char *str, int *i)
{
	int		j;
	char	*tmp1;
	char	*tmp2;
	char	*tmp3;

	j = *i;
	while (str[++(*i)])
		if (str[*i] == '\'')
			break ;
	tmp1 = ft_substr(str, 0, j);
	tmp2 = ft_substr(str, j + 1, *i - j - 1);
	tmp3 = ft_strjoin(tmp1, tmp2);
	free(tmp1);
	free(tmp2);
	tmp1 = ft_substr(str, *i + 1, ft_strlen(str) - j);
	tmp2 = ft_strjoin(tmp3, tmp1);
	free(tmp1);
	free (tmp3);
	free (str);
	(*i)--;
	(*i)--;
	return (tmp2);
}
