/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menv.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbaumeis <lbaumeis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/27 15:51:16 by lbaumeis          #+#    #+#             */
/*   Updated: 2024/07/27 17:40:56 by lbaumeis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "buildins.h"

void	get_menv(t_buildins *vars)
{
	int	x;

	x = 0;
	vars->menv = malloc(sizeof(char *) * (ft_arrlen(vars->envp) + 1));
	if (!vars->menv)
		err_or("malloc");
	while (vars->envp[x])
	{
		vars->menv[x] = ft_strdup(vars->envp[x]);
		if (!vars->menv[x])
		{
			ft_free_double(vars->menv);
			err_or("strdup");
		}
		x++;
	}
	if (x != ft_arrlen(vars->envp))
	{
		ft_free_double(vars->menv);
		err_or("menv");
	}
	vars->menv[x] = NULL;
}
