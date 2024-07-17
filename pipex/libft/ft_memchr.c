/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbaumeis <lbaumeis@student.42vienna.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 16:38:59 by lbaumeis          #+#    #+#             */
/*   Updated: 2023/10/14 08:22:36 by lbaumeis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t			i;
	unsigned char	cval;
	unsigned char	*spoint;

	i = 0;
	cval = (unsigned char)c;
	spoint = (unsigned char *)s;
	while (i < n)
	{
		if (spoint[i] == cval)
			return (&spoint[i]);
		i++;
	}
	return (NULL);
}
