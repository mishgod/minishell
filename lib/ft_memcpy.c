/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbooker <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/28 13:59:58 by rbooker           #+#    #+#             */
/*   Updated: 2020/10/28 14:33:09 by rbooker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t			i;
	unsigned char	*s;
	unsigned char	*d;

	if (!src && !dest)
		return (dest);
	i = 0;
	s = (unsigned char *)src;
	d = dest;
	while (i < n)
	{
		*d++ = *s++;
		i++;
	}
	return (dest);
}
