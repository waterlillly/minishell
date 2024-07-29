/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbaumeis <lbaumeis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 16:40:47 by lbaumeis          #+#    #+#             */
/*   Updated: 2024/07/15 14:31:44 by lbaumeis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	char	*b;
	char	*lil;
	size_t	x;
	size_t	y;

	if (!big || len == 0)
		return (0);
	if (little[0] == '\0')
		return ((char *)big);
	b = (char *)big;
	lil = (char *)little;
	x = 0;
	while (b[x] && x < len)
	{
		y = 0;
		while (b[x + y] && b[x + y] == lil[y] && (x + y) < len)
		{
			if (lil[y + 1] == '\0')
				return (&b[x]);
			y++;
		}
		x++;
	}
	return (NULL);
}
