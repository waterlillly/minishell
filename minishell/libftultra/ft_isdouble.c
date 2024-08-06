/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isdouble.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbaumeis <lbaumeis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/21 12:45:55 by lbaumeis          #+#    #+#             */
/*   Updated: 2024/08/06 18:30:39 by lbaumeis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftultra.h"

int	ft_isdouble(char *nbr)
{
	size_t	x;
	int		d;

	x = 0;
	d = 0;
	if (nbr[x] == '+' || nbr[x] == '-' )
		x++;
	while (nbr[x])
	{
		if (ft_isdigit(nbr[x]))
		{
			x++;
			if (d >= 1 && nbr[x] == '.')
				return (0);
			else if (d < 1 && nbr[x] == '.')
			{
				d++;
				x++;
			}
		}
		else
			break ;
	}
	if (x == ft_strlen(nbr) && nbr[x - 1] != '.')
		return (1);
	return (0);
}
