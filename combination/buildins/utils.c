/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbaumeis <lbaumeis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/27 13:48:57 by lbaumeis          #+#    #+#             */
/*   Updated: 2024/08/07 18:26:08 by lbaumeis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../exec.h"

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

void	buildins_init(t_pipex *p, char **envp)
{
	get_menv(p, envp);
	get_pwd(p);
	go_up_oldpwd(p);
	p->home = get_env(p, "HOME");
	if (!p->home)
		error(p, "get_env failed", p->status);
	p->mpath = get_env(p, "PATH");
	if (!p->home)
		error(p, "get_env failed", p->status);
	//get_cdpath(p);
	combine_export(p);
	//export
	//modify cdpath->if smth inside:
	//	look there first when executing stuff
	//	if not found go from pwd
	//	if not found display error
}
