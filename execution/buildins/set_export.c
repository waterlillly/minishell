/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_export.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbaumeis <lbaumeis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/03 11:59:53 by lbaumeis          #+#    #+#             */
/*   Updated: 2024/08/03 16:45:32 by lbaumeis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "buildins.h"

void	update_export(t_buildins *vars, char *tok, char *token)//token = token[x + 1]
{
	int		x;
	int		y;
	char	*temp;

	x = 0;
	temp = NULL;
	while (vars->export[x])
	{
		y = 11;
		while (tok[y] == vars->export[x][y])
			y++;
		if (tok[y] == '\0' && vars->export[x][y] == '=')
		{
			temp = ft_
		}
		x++;
	}
}

void	set_export(t_buildins *vars, char **token)
{
	int		x;
	int		y;
	char	*temp;

	x = 0;
	y = 0;
	temp = NULL;
	x = find_arg(token, "export");
	if (token[x + 1][0] == '$')
		err_or("not a valid identifier");
	if (valid_env(vars, token[x + 1]) == true)
	{
		temp = strcpy_until(token[x + 1]);
		if (!temp)
			err_or("copy_until");
		y = find_env(vars, temp);
		if (y == -1)
			err_or("couldnt find env");
		else
		{
			vars->menv[y] = ft_strdup(token[x + 1]);
			if (!vars->menv[y])
				err_or("strdup");
		}
	}
}
