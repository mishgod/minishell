#include "../parser/parser.h"

int	change_envp3(char *name, char ***arr, int len, int flag)
{
	int	i;

	i = 0;
	while ((*arr)[i])
	{
		if (cmp_names(name, (*arr)[i]) && !flag)
			return (1);
		if ((flag && name[len - 1] == '+') && (!ft_strncmp((*arr)[i], name, len
				- 1) && ((*arr)[i][len - 1] == '=' || !(*arr)[i][len - 1])))
		{
			if (!(*arr)[i][len - 1])
				len--;
			(*arr)[i] = join_strings_with_free_first((*arr)[i], name + len + 1);
			return (1);
		}
		if (cmp_names(name, (*arr)[i]) && flag)
		{
			free ((*arr)[i]);
			(*arr)[i] = ft_strdup(name);
			return (1);
		}
		i++;
	}
	return (0);
}

char	**change_envp2(char *name, char **arr)
{
	int		len;
	int		flag;
	char	*new_name;

	len = 0;
	flag = 0;
	while (name[len] && name[len] != '=')
		len++;
	if (name[len] == '=')
		flag++;
	if (change_envp3(name, &arr, len, flag))
		return (arr);
	if (flag && name[len - 1] == '+')
	{
		new_name = ft_substr(name, 0, len - 1);
		new_name = join_strings_with_free_first(new_name, name + len);
		arr = add_line(new_name, arr);
		free (new_name);
	}
	else
		arr = add_line(name, arr);
	return (arr);
}

int	export_dst(char *str)
{
	int	i;
	int	j;
	int	k;

	k = 0;
	j = 0;
	i = 0;
	while (str[k] && str[k] != '=')
		k++;
	while (str[i] && str[i] != '+')
		i++;
	while (str[j] && str[j] != '-')
		j++;
	if (str[k] == '=')
	{
		if ((str[i] == '+' && (k != i + 1 && k > i)))
			return (1);
		if ((str[j] == '-' && k > j))
			return (1);
	}
	else if (str[i] == '+' || str[j] == '-')
		return (1);
	if (i == 0 || j == 0 || str[0] == '=')
		return (1);
	return (0);
}
