/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbooker <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/17 17:15:35 by rbooker           #+#    #+#             */
/*   Updated: 2020/11/17 17:15:37 by rbooker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	pretrim(char *s1, char *s2)
{
	int		i;
	int		j;
	int		k;

	i = 0;
	while (s1[i] != '\0')
	{
		j = 0;
		k = 0;
		while (s2[j] != '\0')
		{
			if (s1[i] == s2[j])
				k = 1;
			j++;
		}
		if (k)
			i++;
		else
			break ;
	}
	return (i);
}

static int	posttrim(char *s1, char *s2)
{
	int		i;
	int		j;
	int		k;

	i = ft_strlen(s1) - 1;
	while (i >= 0)
	{
		j = 0;
		k = 0;
		while (s2[j] != '\0')
		{
			if (s1[i] == s2[j])
				k = 1;
			j++;
		}
		if (k)
			i--;
		else
			break ;
	}
	return (i);
}

char	*ft_strtrim(char const *s1, char const *s2)
{
	char	*str1;
	char	*str2;
	char	*str;
	int		pre;
	int		post;

	if (!s1)
		return (0);
	str1 = (char *)s1;
	str2 = (char *)s2;
	pre = pretrim(str1, str2);
	post = posttrim(str1, str2);
	if (post >= 0)
	{
		str = (char *)malloc((post - pre + 2) * sizeof(char));
		if (!str)
			return (0);
		ft_strlcpy(str, &str1[pre], (post - pre + 2));
	}
	else
		str = ft_calloc(1, sizeof(char));
	return (str);
}
