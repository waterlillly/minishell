/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbaumeis <lbaumeis@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 17:40:20 by lbaumeis          #+#    #+#             */
/*   Updated: 2024/08/14 15:52:04 by lbaumeis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	size;
	size_t	i;
	char	*src;
	char	*sub;

	if (!s)
		return (NULL);
	if (start >= ft_strlen(s))
		return (ft_strdup(""));
	i = 0;
	src = (char *)s;
	size = ft_strlen(s) - start;
	if (len > size)
		len = size;
	sub = (char *)malloc(sizeof(char) * (len + 1));
	if (!sub)
		return (NULL);
	while (src[i] && i < len)
	{
		sub[i] = src[start + i];
		i++;
	}
	sub[i] = '\0';
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