/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbooker <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/17 17:15:47 by rbooker           #+#    #+#             */
/*   Updated: 2020/11/17 17:16:46 by rbooker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*p;
	size_t	i;
	size_t	k;
	size_t	j;

	i = 0;
	j = 0;
	k = start;
	if (!s)
		return (0);
	while (s[k++] != '\0')
		j++;
	if (start > ft_strlen((char *)s))
		return (ft_calloc(1, sizeof(char)));
	if (len > k)
		p = (char *)malloc((j + 1) * sizeof(char));
	else
		p = (char *)malloc((len + 1) * sizeof(char));
	if (!p)
		return (0);
	while (len-- != 0 && j-- != 0)
		p[i++] = s[start++];
	p[i] = '\0';
	return (p);
}
