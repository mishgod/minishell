/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbooker <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/16 18:03:02 by rbooker           #+#    #+#             */
/*   Updated: 2020/11/16 18:07:20 by rbooker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	length_src;
	size_t	length_dst;

	length_src = ft_strlen((char *)src);
	length_dst = ft_strlen(dst);
	dst += length_dst;
	if (length_dst < size)
	{
		while (size - length_dst - 1 && *src)
		{
			*dst++ = *src++;
			size--;
		}
	}
	else
		return (size + length_src);
	*dst = '\0';
	return (length_dst + length_src);
}
