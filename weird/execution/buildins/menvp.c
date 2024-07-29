/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menvp.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbaumeis <lbaumeis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/27 13:17:02 by lbaumeis          #+#    #+#             */
/*   Updated: 2024/07/29 13:24:31 by lbaumeis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "buildins.h"

void	get_menvp(t_buildins *vars)
{
	vars->menvp = get_env(vars, "PATH");
	if (!vars->menvp)
	{
		perror(vars->menvp);
		exit(EXIT_FAILURE);
	}
}

/*
void	get_menvp(t_buildins *vars)
{
	int	i;
	int	j;

	i = 0;
	j = 5;
	while (ft_strncmp(vars->menv[i], "PATH", 4))
		i++;
	vars->menvp = malloc(sizeof(char) * (ft_strlen(vars->menv[i]) - 3));
	if (!vars->menvp)
		err_or("malloc");
	while (vars->menv[i][j])
	{
		*vars->menvp = vars->menv[i][j];
		j++;
		vars->menvp++;
	}
	*vars->menvp = '\0';
}
*/