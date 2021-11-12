/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbooker <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/16 18:08:37 by rbooker           #+#    #+#             */
/*   Updated: 2020/11/16 18:09:01 by rbooker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	char	*h;
	char	*n;
	int		k;
	int		i;

	h = (char *)haystack;
	n = (char *)needle;
	k = ft_strlen(n);
	if (!k)
		return (h);
	i = (int)len - ft_strlen(n);
	while (*h && i >= 0)
	{
		if (*h == *n)
		{
			if (!ft_strncmp(h, n, k))
				return (h);
		}
		h++;
		i--;
	}
	return (0);
}
