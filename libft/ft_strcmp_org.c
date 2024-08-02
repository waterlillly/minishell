/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp_org.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbaumeis <lbaumeis@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/02 14:55:27 by lbaumeis          #+#    #+#             */
/*   Updated: 2024/08/02 17:57:26 by lbaumeis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
	if return > 0: first is before second (so dont change anything)
	else if return < 0: swap first and second
	else if return == 0: they are the same
*/

int	ft_strcmp_org(const char *s1, const char *s2)
{
	int	x;
	int	len_s1;
	int	len_s2;

	x = 0;
	if (!s1 || !s2)
		return (0);
	len_s1 = ft_strlen(s1);
	len_s2 = ft_strlen(s2);
	while (s1[x] && s2[x] && s1[x] == s2[x])
		x++;
	if (x == len_s1 && len_s1 == len_s2)
		return (0);
	else
		return (s2[x] - s1[x]);
}
