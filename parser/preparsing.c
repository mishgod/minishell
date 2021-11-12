#include "parser.h"

static int	check_quoter(char *str, int *num, int *i, char q)
{
	if (str[*i] == q)
	{
		(*i)++;
		(*num)++;
		if (q == '\'')
			while (str[*i] != q && str[*i])
				(*i)++;
		else
			while (!(str[*i] == '\"' && str[*i - 1] != '\\') && str[*i])
				(*i)++;
		if (str[*i] == q)
		{
			(*num)++;
			(*i)++;
		}
		else
			return (1);
	}
	return (0);
}

static void	loop(char *str, int *num_1_q, int *num_2_q, int *i)
{
	while (str[*i])
	{
		if (str[*i] == '\'')
		{
			if (check_quoter(str, num_1_q, i, str[*i]))
				break ;
		}
		else if (str[*i] == '\"')
		{
			if (check_quoter(str, num_2_q, i, str[*i]))
				break ;
		}
		else if (str[*i] == '\\')
		{
			if (str[*i + 1])
				*i += 2;
			else
				(*i)++;
		}
		else
			(*i)++;
	}
}

static int	check_errors(char *str, int num_1_q, int num_2_q, int i)
{
	if (str[i - 1] == '\\')
	{
		printf("minishell: open \\ slash\n");
		g_errnum = 258;
		return (1);
	}
	if (num_1_q % 2 == 1)
	{
		printf("minishell: unnecessary \' quote\n");
		g_errnum = 258;
		return (1);
	}
	if (num_2_q % 2 == 1)
	{
		printf("minishell: unnecessary \" quote\n");
		g_errnum = 258;
		return (1);
	}
	return (0);
}

int	ft_preparsing(char *str)
{
	int	i;
	int	num_1_q;
	int	num_2_q;

	i = 0;
	num_1_q = 0;
	num_2_q = 0;
	loop(str, &num_1_q, &num_2_q, &i);
	if (check_errors(str, num_1_q, num_2_q, i))
		return (1);
	return (0);
}
