/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbooker <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/16 18:07:45 by rbooker           #+#    #+#             */
/*   Updated: 2020/11/16 18:12:00 by rbooker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int		i;
	char	*ch;

	ch = (char *)s;
	i = ft_strlen(ch);
	if (c == 0)
		return (&ch[i]);
	i--;
	while (i >= 0)
	{
		if (ch[i] == c)
			return (&ch[i]);
		i--;
	}
	return (0);
}
