/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbooker <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/16 18:10:33 by rbooker           #+#    #+#             */
/*   Updated: 2020/11/16 18:12:18 by rbooker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *src)
{
	char	*str;
	int		i;
	char	*newsrc;

	newsrc = (char *)src;
	i = 0;
	str = (char *)malloc((ft_strlen(newsrc) + 1) * sizeof(char));
	if (!str)
		return (0);
	while (src[i] != '\0')
	{
		str[i] = newsrc[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}
