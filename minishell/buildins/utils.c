/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbaumeis <lbaumeis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/27 13:48:57 by lbaumeis          #+#    #+#             */
/*   Updated: 2024/08/07 13:25:58 by lbaumeis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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

void	err_free_buildins(t_ms *ms)
{
	if (ms->e->menv)
		free_double(ms->e->menv);
	if (ms->e->mpath)
		free(ms->e->mpath);
	if (ms->e->xport)
		free_double(ms->e->xport);
	if (ms->e->home)
		free(ms->e->home);
	if (ms->e->oldpwd)
		free(ms->e->oldpwd);
	if (ms->e->pwd)
		free(ms->e->pwd);
}
