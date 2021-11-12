/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbooker <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/29 16:29:12 by rbooker           #+#    #+#             */
/*   Updated: 2020/10/29 18:13:14 by rbooker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	char_to_int(int i, const char *str, int k)
{
	int			j;
	int			l;
	long long	num;

	num = 0;
	l = 0;
	while (str[i] != '\0' && str[i] <= '9' && str[i] >= '0' && l < 12)
	{
		j = str[i] - '0';
		i++;
		l++;
		num = 10 * num + j;
	}
	if (k * num > 2147483647)
		return (-1);
	else if (k * num < -2147483648)
		return (0);
	else
		return (k * num);
}

int	ft_atoi(const char *str)
{
	int		i;
	int		j;
	int		num;

	i = 0;
	j = 1;
	while (str[i] == 32 || (str[i] > 8 && str[i] < 14))
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			j = -1;
		i++;
	}
	num = char_to_int(i, str, j);
	return (num);
}
