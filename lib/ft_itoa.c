/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbooker <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/17 17:14:53 by rbooker           #+#    #+#             */
/*   Updated: 2020/11/17 17:14:59 by rbooker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	number_of_symbols(int n)
{
	int		i;

	if (n == 0)
		return (1);
	i = 0;
	while (n != 0)
	{
		n /= 10;
		i++;
	}
	return (i);
}

static char	*negative(int n, int i, char *str)
{
	str[i] = '\0';
	i--;
	if (n == -2147483648)
	{
		n = 214748364;
		str[i] = '8';
	}
	else
	{
		str[i] = -n % 10 + '0';
		n = -n / 10;
	}
	i--;
	while (i >= 1)
	{
		str[i] = n % 10 + '0';
		n /= 10;
		i--;
	}
	str[i] = '-';
	return (str);
}

static char	*positive(int num, int i, char *str)
{
	str[i] = '\0';
	i--;
	while (i >= 0)
	{
		str[i] = num % 10 + '0';
		num /= 10;
		i--;
	}
	return (str);
}

char	*ft_itoa(int n)
{
	char	*str;
	int		i;

	i = number_of_symbols(n);
	if (n < 0)
	{
		str = malloc(i + 2);
		if (!str)
			return (0);
		str = negative(n, i + 1, str);
		return (str);
	}
	else if (n >= 0)
	{
		str = (char *)malloc((i + 1) * sizeof(char));
		if (!str)
			return (0);
		str = positive(n, i, str);
		return (str);
	}
	else
	{
		str = "0";
		return (str);
	}
}
