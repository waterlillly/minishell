/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   home.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbaumeis <lbaumeis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/27 14:06:16 by lbaumeis          #+#    #+#             */
/*   Updated: 2024/07/27 17:18:20 by lbaumeis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "buildins.h"

void	get_home(t_buildins *vars)
{
	vars->home = getenv("HOME");
	if (!vars->home)
	{
		perror(vars->home);
		exit(EXIT_FAILURE);
	}
}
