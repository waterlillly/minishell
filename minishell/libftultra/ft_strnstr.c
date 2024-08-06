/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbaumeis <lbaumeis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 16:40:47 by lbaumeis          #+#    #+#             */
/*   Updated: 2024/08/06 18:36:23 by lbaumeis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftultra.h"

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

/*
char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	if ((!big && len == 0) || (len < ft_strlen(little) && !ft_strlen(big)))
		return (NULL);
	if (!*little && big)
		return ((char *)big);
	while (big[i] && i < len)
	{
		while (big[i + j] && big[i + j] == little[j] && i + j < len)
			j++;
		if (!little[j])
			return ((char *)(big + i));
		j = 0;
		i++;
	}
	return (NULL);
}
*/