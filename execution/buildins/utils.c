/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbaumeis <lbaumeis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/27 13:48:57 by lbaumeis          #+#    #+#             */
/*   Updated: 2024/08/05 12:24:38 by lbaumeis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "buildins.h"

int	how_many(char **s, char *o)
{
	int	x;
	int	y;

	x = 0;
	y = 0;
	while (s[x])
	{
		if (ft_strcmp(s[x], o))
			y++;
		x++;
	}
	return (y);
}

bool	is_access(char *dir)
{
	if ((access(dir, F_OK) == 0))
		return (true);
	return (false);
}

void	err_or(char *s)
{
	perror(s);
	exit(EXIT_FAILURE);
}

int	find_arg(char **s, char *a)
{
	int	x;

	x = 0;
	if (!s || !a)
		return (-1);
	while (s[x])
	{
		if (ft_strcmp(s[x], a))
			return (x);
		x++;
	}
	return (-1);
}

void	buildins_init(t_buildins *vars)
{
	get_menv(vars);
	get_pwd(vars);
	go_up_oldpwd(vars);
	vars->home = get_env(vars, "HOME");
	if (!vars->home)
		err_or("get_env failed");
	vars->mpath = get_env(vars, "PATH");
	if (!vars->home)
		err_or("get_env failed");
	//get_cdpath(vars);
	combine_export(vars);
	//export
	//modify cdpath->if smth inside:
	//	look there first when executing stuff
	//	if not found go from pwd
	//	if not found display error
}
