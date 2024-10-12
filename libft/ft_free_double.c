/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_double.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbaumeis <lbaumeis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/27 17:00:57 by lbaumeis          #+#    #+#             */
/*   Updated: 2024/10/12 17:42:45 by lbaumeis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_free_double(char **smth)
{
	int	x;

	if (!smth)
		return ;
	x = ft_arrlen(smth);
	while (smth[x])
	{
		free(smth[x]);
		smth[x] = NULL;
		x--;
	}
	if (smth)
		free(smth);
	smth = NULL;
}
