/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr_bool.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbaumeis <lbaumeis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/05 16:31:22 by lbaumeis          #+#    #+#             */
/*   Updated: 2024/08/05 17:18:15 by lbaumeis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "buildins.h"

bool	ft_strnstr_bool(const char *big, const char *lil, int start, int len)
{
	int	x;

	if (!big || len == 0 || lil[0] == '\0')
		return (false);
	x = 0;
	while (big[start] && lil[x] && x < len && big[start] == lil[x])
	{
		start++;
		x++;
	}
	if (x == len && big[start - 1] == lil[x - 1] && lil[x] == '\0')
		return (true);
	return (false);
}
