/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgardesh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 14:27:10 by mgardesh          #+#    #+#             */
/*   Updated: 2023/09/05 14:29:26 by mgardesh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	dest_len;
	size_t	src_len;
	size_t	i;

	src_len = ft_strlen(src);
	if ((size == 0 && !dst) || size < ft_strlen(dst))
		return (src_len + size);
	dest_len = ft_strlen(dst);
	i = 0;
	while (src[i] != '\0' && ((i + dest_len) < size - 1) && size > 0)
	{
		dst[dest_len + i] = (unsigned char)src[i];
		i++;
	}
	dst[dest_len + i] = '\0';
	return (src_len + dest_len);
}
