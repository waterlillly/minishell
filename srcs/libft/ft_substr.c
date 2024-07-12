/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgardesh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/06 16:03:03 by mgardesh          #+#    #+#             */
/*   Updated: 2023/09/06 16:27:52 by mgardesh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

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
