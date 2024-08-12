/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbaumeis <lbaumeis@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 16:40:17 by lbaumeis          #+#    #+#             */
/*   Updated: 2024/06/25 14:45:30 by lbaumeis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t	s;
	size_t	srclen;

	if (!dst || !src)
		return (0);
	s = 0;
	srclen = ft_strlen(src);
	if (size == 0)
		return (srclen);
	while (src[s] != '\0' && s < size - 1)
	{
		dst[s] = src[s];
		s++;
	}
	dst[s] = '\0';
	return (srclen);
}
