/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbaumeis <lbaumeis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/03 12:07:28 by lbaumeis          #+#    #+#             */
/*   Updated: 2024/08/03 16:07:40 by lbaumeis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "buildins.h"

int	find_env(t_buildins *vars, char *tok)
{
	int	x;
	int	y;

	x = 0;
	while (vars->menv[x])
	{
		y = 0;
		while (tok[y] == vars->menv[x][y])
			y++;
		if (tok[y] == '\0' && vars->menv[x][y] == '=')
			return (x);
		x++;
	}
	return (-1);
}

bool	valid_env(t_buildins *vars, char *tok)
{
	int	x;
	int	y;

	x = 0;
	while (vars->menv[x])
	{
		y = 0;
		while (tok[y] == vars->menv[x][y])
		{
			y++;
			if (tok[y] == '=' && vars->menv[x][y] == '=')
				return (true);
		}
		x++;
	}
	return (false);
}
