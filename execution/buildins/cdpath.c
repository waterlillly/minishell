/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cdpath.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbaumeis <lbaumeis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 12:50:15 by lbaumeis          #+#    #+#             */
/*   Updated: 2024/07/30 12:50:26 by lbaumeis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "buildins.h"

void	set_cdpath(t_buildins *vars, char **token)
{
	char	**temp;
	int		x;

	temp = NULL;
	x = find_arg(token, "export");
	if (x != -1 && ft_strcmp(token[x + 1], "CDPATH") && token[x + 2])
	{
		temp = ft_split(token[x + 2], ':');
		if (!temp)
			err_or("split");
		while (*temp)
		{
			if (access(*temp, F_OK) == -1)
			{
				ft_free_double(temp);
				err_or("access");
			}
			temp++;
		}
		ft_free_double(temp);
		vars->cdpath = ft_strdup(token[x + 2]);
		if (!vars->cdpath)
			err_or("strdup");
	}
}

void	get_cdpath(t_buildins *vars)
{
	if (!vars->cdpath)
		vars->cdpath = ft_strdup("\n");
	else
		err_or("not done yet");
}
