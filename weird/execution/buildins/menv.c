/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menv.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbaumeis <lbaumeis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/27 15:51:16 by lbaumeis          #+#    #+#             */
/*   Updated: 2024/07/29 11:32:30 by lbaumeis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "buildins.h"

void	get_menv(t_buildins *vars, char **envp)
{
	int	x;

	x = 0;
	vars->menv = malloc(sizeof(char *) * (ft_arrlen(envp) + 1));
	if (!vars->menv)
		err_or("malloc");
	while (envp[x])
	{
		vars->menv[x] = ft_strdup(envp[x]);
		if (!vars->menv[x])
		{
			ft_free_double(vars->menv);
			err_or("strdup");
		}
		x++;
	}
	if (x != ft_arrlen(envp))
	{
		ft_free_double(vars->menv);
		err_or("menv");
	}
	vars->menv[x] = NULL;
}
