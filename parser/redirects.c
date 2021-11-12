#include "parser.h"

char	*remove_redirects(t_par *par, char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\"' || str[i] == '\'')
			skip_quoters(str, &i, str[i]);
		else if (str[i] == '<' || str[i] == '>')
			str = ft_redirects(str, &i, par);
		else if (str[i] == '\\')
			i += 2;
		else
			i++;
		if (!str)
			return (str);
	}
	return (str);
}

char	*ft_redir_open(char *str, int *i, t_par *par)
{
	int		j;
	int		k;
	char	*file_name;

	j = *i;
	(*i)++;
	k = check_in_redirect(par, str, i, "<");
	if (k == -1)
		return (NULL);
	file_name = ft_substr(str, k, *i - k);
	file_name = parser_filename(par, file_name);
	str = input_value_to_string(str, "", *i - j, j);
	if (par->flag.red_r)
		close(par->fd_redirect_r);
	par->fd_redirect_r = open(file_name, O_RDONLY, 0644);
	if (par->fd_redirect_r == -1)
		error_open(&str, file_name);
	else
		par->flag.red_r = 1;
	free(file_name);
	*i = j;
	return (str);
}

char	*ft_double_redir_write(char *str, int *i, t_par *par)
{
	int		j;
	int		k;
	char	*file_name;

	j = *i;
	*i += 2;
	k = check_in_redirect(par, str, i, ">>");
	if (k == -1)
		return (NULL);
	file_name = ft_substr(str, k, *i - k);
	file_name = parser_filename(par, file_name);
	str = input_value_to_string(str, "", *i - j, j);
	if (par->flag.red_w)
		close(par->fd_redirect_w);
	par->fd_redirect_w = open(file_name, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (par->fd_redirect_w == -1)
		error_open(&str, file_name);
	else
		par->flag.red_w = 1;
	free(file_name);
	*i = j;
	return (str);
}

char	*ft_redir_write(char *str, int *i, t_par *par)
{
	int		j;
	int		k;
	char	*file_name;

	j = *i;
	(*i)++;
	k = check_in_redirect(par, str, i, ">");
	if (k == -1)
		return (NULL);
	file_name = ft_substr(str, k, *i - k);
	file_name = parser_filename(par, file_name);
	str = input_value_to_string(str, "", *i - j, j);
	if (par->flag.red_w)
		close(par->fd_redirect_w);
	par->fd_redirect_w = open(file_name, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (par->fd_redirect_w == -1)
		error_open(&str, file_name);
	else
		par->flag.red_w = 1;
	free(file_name);
	*i = j;
	return (str);
}

char	*ft_redirects(char *str, int *i, t_par *par)
{
	if (str[*i] == '<' && str[*i + 1] != '<')
		str = ft_redir_open(str, i, par);
	else if (str[*i] == '<' && str[*i + 1] == '<')
		str = ft_double_redir_open(str, i, par);
	else if (str[*i] == '>' && str[*i + 1] != '>')
		str = ft_redir_write(str, i, par);
	else if (str[*i] == '>' && str[*i + 1] == '>')
		str = ft_double_redir_write(str, i, par);
	return (str);
}
