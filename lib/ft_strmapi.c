/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbooker <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/19 15:42:08 by rbooker           #+#    #+#             */
/*   Updated: 2020/11/19 15:42:12 by rbooker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	unsigned int	i;
	char			*str;

	if (!s || !(f))
		return (0);
	i = ft_strlen((char *)s);
	str = (char *)malloc((i + 1) * sizeof(char));
	if (!str)
		return (0);
	str[i] = '\0';
	while (i--)
		str[i] = f(i, s[i]);
	return (str);
}
