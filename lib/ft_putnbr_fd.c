/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbooker <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/17 18:17:36 by rbooker           #+#    #+#             */
/*   Updated: 2020/11/17 18:17:38 by rbooker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	neg(int n, int i, char *str, int fd)
{
	int		num;

	if (n == -2147483648)
	{
		write(fd, "-2147483648", 11);
	}
	else
	{
		num = -n;
		str[i] = '\0';
		i--;
		while (i >= 1)
		{
			str[i] = num % 10 + '0';
			num /= 10;
			i--;
		}
		str[i] = '-';
		while (str[i] != '\0')
			write(fd, &str[i++], 1);
	}
}

static void	pos(int num, int i, char *str, int fd)
{
	str[i] = '\0';
	i--;
	while (i >= 0)
	{
		str[i] = num % 10 + '0';
		num /= 10;
		i--;
	}
	i++;
	while (str[i] != '\0')
		write(fd, &str[i++], 1);
}

void	ft_putnbr_fd(int n, int fd)
{
	char	str[11];
	int		i;
	int		num;

	i = 0;
	num = n;
	while (n != 0)
	{
		n /= 10;
		i++;
	}
	if (num < 0)
		neg(num, i + 1, str, fd);
	else if (num > 0)
		pos(num, i, str, fd);
	else
		write(fd, "0", 1);
}
