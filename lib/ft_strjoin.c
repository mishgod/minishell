/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbooker <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/17 17:15:17 by rbooker           #+#    #+#             */
/*   Updated: 2020/11/17 17:15:20 by rbooker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*join(char *s, char *s1, char *s2)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (s1[i] != '\0')
	{
		s[i] = s1[i];
		i++;
	}
	while (s2[j] != '\0')
		s[i++] = s2[j++];
	s[i] = '\0';
	return (s);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*s11;
	char	*s21;
	char	*s;

	if (!s1 && s2)
		return ((char *)s2);
	if (s1 && !s2)
		return ((char *)s1);
	s11 = (char *)s1;
	s21 = (char *)s2;
	s = (char *)malloc((ft_strlen(s11) + ft_strlen(s21) + 1) * sizeof(char));
	if (!s)
		return (0);
	s = join(s, s11, s21);
	return (s);
}
