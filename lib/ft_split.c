/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncammy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/19 20:54:16 by ncammy            #+#    #+#             */
/*   Updated: 2021/07/14 11:05:00 by ncammy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_words(char const *s, char c)
{
	size_t	count;

	count = 0;
	while (*s)
	{
		while (*s == c && *s)
			s++;
		if (*s)
			count++;
		while (*s && *s != c)
			s++;
	}
	return (count);
}

static char	**ft_free(char **ss, long i)
{
	while (i >= 0)
	{
		free(ss[i]);
		i--;
	}
	free(ss);
	return (0);
}

char	**ft_split(char const *s, char c)
{
	size_t	i;
	size_t	len;
	char	**ss;

	ss = (char **)ft_calloc(ft_words(s, c) + 1, sizeof(char *));
	if (!s || !ss)
		return (0);
	i = 0;
	len = 0;
	while (*s)
	{
		len = 0;
		while (*s == c && *s)
			s++;
		while (*s && *s != c)
		{
			len++;
			s++;
		}
		if (len)
			ss[i++] = ft_substr(s - len, 0, len);
		if (!ss[i - 1])
			return (ft_free(ss, i - 1));
	}
	return (ss);
}
