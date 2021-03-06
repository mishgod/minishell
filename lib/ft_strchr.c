/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbooker <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/16 18:10:50 by rbooker           #+#    #+#             */
/*   Updated: 2020/11/16 18:12:27 by rbooker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

char	*ft_strchr(const char *s, int c)
{
	int		i;
	char	*ch;

	ch = (char *)s;
	i = 0;
	while (ch[i] != '\0')
	{
		if (ch[i] == c)
			return (&ch[i]);
		i++;
	}
	if (c == 0)
		return (&ch[i]);
	return (0);
}
