#include "parser.h"

static void	number_of_words(char *str, int *num)
{
	int		k;
	int		flag;

	k = 0;
	while (str[k])
	{
		flag = 0;
		while ((str[k] == 9 || str[k] == 32) && str[k])
			k++;
		while (str[k] != 9 && str[k] != 32 && str[k])
		{
			if (str[k] == '\'' || str[k] == '\"')
				skip_quoters(str, &k, str[k]);
			else
				k++;
			flag++;
		}
		if (flag)
			(*num)++;
	}
}

int	cycle_split(char *str, char **arr)
{
	int		k;
	int		i;
	int		begin;

	k = 0;
	i = 0;
	while (str[k])
	{
		while ((str[k] == 9 || str[k] == 32) && str[k])
			k++;
		begin = k;
		while (str[k] != 9 && str[k] != 32 && str[k])
		{
			if (str[k] == '\"' || str[k] == '\'')
				skip_quoters(str, &k, str[k]);
			else if (str[k] == '\\')
				k += 2;
			else
				k++;
		}
		if (begin != k)
			arr[i++] = ft_substr(str, begin, k - begin + 1);
	}
	arr[i] = NULL;
	return (0);
}

static char	**error_free_arr(char **arr, int i)
{
	i--;
	while (i >= 0)
		free (arr[i--]);
	free (arr);
	return (NULL);
}

char	**new_split(t_par *par, char *str)
{
	int		num;
	char	**arr;
	int		i;

	num = 0;
	number_of_words(str, &num);
	arr = ft_calloc(num + 1, sizeof(char *));
	if (!num)
	{
		arr[0] = NULL;
		return (arr);
	}
	cycle_split(str, arr);
	free (str);
	i = 0;
	while (arr[i])
	{
		arr[i] = parser_one_command(par, arr[i]);
		if (!arr[i])
			return (error_free_arr(arr, i));
		i++;
	}
	return (arr);
}
