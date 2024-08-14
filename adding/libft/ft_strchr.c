/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbaumeis <lbaumeis@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 16:39:36 by lbaumeis          #+#    #+#             */
/*   Updated: 2024/08/14 15:50:42 by lbaumeis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	int		i;
	char	find;
	char	*str;

	i = 0;
	if (!s)
		return (NULL);
	find = (char)c;
	str = (char *)s;
	while (str[i])
	{
		if (str[i] == find)
			return (&str[i]);
		else
			i++;
	}
	if (find == '\0')
		return (&str[i]);
	else
		return (NULL);
}

/*
char	*ft_strchr(const char *s, int c)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if ((unsigned char)s[i] == (unsigned char)c)
			return ((char *)s + i);
		i++;
	}
	if ((const char)c == s[i])
		return ((char *)s + i);
	return (NULL);
}
*/