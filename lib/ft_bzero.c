/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbooker <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/28 13:37:19 by rbooker           #+#    #+#             */
/*   Updated: 2020/10/28 13:47:16 by rbooker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_bzero(void *mem, size_t num)
{
	unsigned char	*p;
	size_t			i;

	i = 0;
	p = mem;
	while (i < num)
	{
		*p = 0;
		p++;
		i++;
	}
	return (mem);
}
