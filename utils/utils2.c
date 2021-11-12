#include "../libshell.h"

char	*join_strings_with_free_first(char *str1, char *str2)
{
	char	*new_str;

	new_str = ft_strjoin(str1, str2);
	free (str1);
	return (new_str);
}

char	*input_value_to_string(char *str, char *str_var, int len, int begin)
{
	char	*tmp_first;
	char	*tmp_last;

	tmp_first = ft_substr(str, 0, begin);
	tmp_last = ft_substr(str, begin + len, ft_strlen(str) - begin - len);
	free (str);
	str = ft_strjoin(tmp_first, str_var);
	str = join_strings_with_free_first(str, tmp_last);
	free (tmp_last);
	free (tmp_first);
	return (str);
}

void	free_arr(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
		free(arr[i++]);
	free(arr);
}
