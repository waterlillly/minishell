/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbaumeis <lbaumeis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 16:39:22 by lbaumeis          #+#    #+#             */
/*   Updated: 2024/08/06 18:33:49 by lbaumeis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftultra.h"

static void	*ft_revmem(void *dest, const void *src, size_t n)
{
	int			i;
	const char	*csrc;
	char		*cdest;

	i = (int)n - 1;
	csrc = (const char *)src;
	cdest = (char *)dest;
	while (i >= 0)
	{
		cdest[i] = csrc[i];
		i--;
	}
	return (dest);
}

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	if (!dest || !src || n == 0)
		return (NULL);
	if (src > dest)
		ft_memcpy(dest, src, n);
	else
		ft_revmem(dest, src, n);
	return (dest);
}

/*
void	*ft_memmove(void *dest, const void *src, size_t n)
{
	unsigned char	*ptr1;
	unsigned char	*ptr2;

	if (!(char *)src && !(char *)dest)
		return (NULL);
	ptr1 = (unsigned char *)dest;
	ptr2 = (unsigned char *)src;
	if (ptr1 < ptr2)
		while (n--)
			*ptr1++ = *ptr2++;
	else
	{
		ptr1 = ptr1 + (n - 1);
		ptr2 = ptr2 + (n - 1);
		while (n--)
			*ptr1-- = *ptr2--;
	}
	return (dest);
}
*/