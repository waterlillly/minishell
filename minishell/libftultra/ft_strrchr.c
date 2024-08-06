/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbaumeis <lbaumeis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 16:41:03 by lbaumeis          #+#    #+#             */
/*   Updated: 2024/08/06 18:36:29 by lbaumeis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftultra.h"

char	*ft_strrchr(const char *s, int c)
{
	size_t	i;
	char	*str;
	char	find;

	if (!s)
		return (NULL);
	i = ft_strlen(s);
	str = (char *)s;
	find = (char)c;
	while (i > 0)
	{
		if (c == '\0')
			return (&str[i]);
		if (str[i] == find)
			return (&str[i]);
		else
			i--;
	}
	if (str[0] == find)
		return (&str[i]);
	return (NULL);
}

/*
char	*ft_strrchr(const char *s, int c)
{
	int	i;

	i = ft_strlen(s);
	while (i >= 0)
	{
		if (s[i] == (const unsigned char)c)
			return ((char *)s + i);
		i--;
	}
	return (NULL);
}
*/