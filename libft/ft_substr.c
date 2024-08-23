/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbaumeis <lbaumeis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 17:40:20 by lbaumeis          #+#    #+#             */
/*   Updated: 2024/08/23 14:46:41 by lbaumeis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	char	*src;
	char	*sub;

	if (!s || ft_strlen(s) == 0)
		return (NULL);
	if ((size_t)start >= ft_strlen(s))
	{
		sub = ft_strdup("");
		return (sub);
	}
	i = 0;
	src = (char *)s;
	if (len > ft_strlen(s) - (size_t)start)
		len = ft_strlen(s) - (size_t)start;
	sub = NULL;
	sub = (char *)ft_calloc((len + 1), sizeof(char));
	if (!sub)
		return (NULL);
	while (i < len && src[start + i])
	{
		sub[i] = src[(size_t)start + i];
		i++;
	}
	return (sub);
}

/*
char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	lens;
	char	*out;

	if (!s)
		return (NULL);
	lens = ft_strlen(s);
	len = (unsigned int)len;
	if (start > lens || len * lens == 0)
	{
		out = (char *)ft_calloc(1, sizeof(char));
		if (!out)
			return (out);
		return (out);
	}
	if (len + start > lens)
		out = (char *)ft_calloc((lens - start + 1), sizeof(char));
	else
		out = (char *)ft_calloc((len + 1), sizeof(char));
	if (!out)
		return (out);
	ft_strlcpy(out, s + start, len + 1);
	return (out);
}
*/