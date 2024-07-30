/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbaumeis <lbaumeis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/27 12:47:48 by lbaumeis          #+#    #+#             */
/*   Updated: 2024/07/30 12:59:15 by lbaumeis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "buildins.h"

void	reset_old_pwd(t_buildins *vars, char *path)
{
	char	*temp;

	temp = NULL;
	temp = ft_strdup(vars->oldpwd);
	if (!temp)
		err_or("strdup or no vars->oldpwd");
	free(vars->oldpwd);
	vars->oldpwd = NULL;
	vars->oldpwd = ft_strdup(vars->pwd);
	if (!vars->oldpwd)
		err_or(vars->oldpwd);
	if (access(path, F_OK) == 0)
	{
		free(vars->pwd);
		vars->pwd = NULL;
		vars->pwd = ft_strdup(path);
		if (!vars->pwd)
			err_or("strdup");
	}
	else
	{
		vars->oldpwd = ft_strdup(temp);
		err_or("access");
	}
}

void	join_oldpwd(t_buildins *vars, char **temp, char *oldpwd)
{
	int	x;

	x = 0;
	while (temp[x])
	{
		if (temp[x + 1] == NULL)
		{
			free(temp[x]);
			temp[x] = NULL;
			vars->oldpwd = ft_strjoin_free_one(oldpwd, NULL);
			if (!oldpwd)
				err_or("vars->oldpwd");
			break ;
		}
		oldpwd = ft_strjoin_free_one(oldpwd, "/");
		if (!oldpwd)
			err_or("oldpwd");
		oldpwd = ft_strjoin_free_both(oldpwd, temp[x]);
		if (!oldpwd)
			err_or("oldpwd");
		x++;
	}
	temp = NULL;
}

void	go_up_oldpwd(t_buildins *vars)
{
	char	**temp;
	char	*oldpwd;

	temp = NULL;
	oldpwd = NULL;
	if (!vars->pwd)
		get_pwd(vars);
	temp = ft_split(vars->pwd, '/');
	if (!temp)
		err_or("temp");
	oldpwd = ft_strdup("");
	if (!oldpwd)
		err_or("strdup");
	join_oldpwd(vars, temp, oldpwd);
}
