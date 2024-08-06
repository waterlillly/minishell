/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_double.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbaumeis <lbaumeis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/27 17:00:57 by lbaumeis          #+#    #+#             */
/*   Updated: 2024/08/06 18:30:08 by lbaumeis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftultra.h"

void	ft_free_double(char **smth)
{
	int		x;

	x = 0;
	while (smth[x])
		x++;
	x--;
	while (x >= 0)
	{
		free(smth[x]);
		smth[x] = NULL;
		x--;
	}
	smth = NULL;
}
