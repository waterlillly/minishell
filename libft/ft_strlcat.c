/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbaumeis <lbaumeis@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 16:40:09 by lbaumeis          #+#    #+#             */
/*   Updated: 2024/08/14 15:51:15 by lbaumeis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	x;
	size_t	y;
	size_t	z;

	x = 0;
	if (!dst && !src)
		return (0);
	y = ft_strlen(dst);
	z = ft_strlen(src);
	if (y >= size || size == 0)
		return (z + size);
	while (src[x] != '\0' && (x + y) < size - 1)
	{
		dst[y + x] = src[x];
		x++;
	}
	dst[y + x] = '\0';
	return (y + z);
}

/*
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
*/