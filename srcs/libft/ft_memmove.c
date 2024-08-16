/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgardesh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 14:19:43 by mgardesh          #+#    #+#             */
/*   Updated: 2023/09/05 14:21:26 by mgardesh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

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
