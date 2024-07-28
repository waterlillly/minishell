/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbaumeis <lbaumeis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/27 12:47:48 by lbaumeis          #+#    #+#             */
/*   Updated: 2024/07/28 12:24:08 by lbaumeis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "buildins.h"

void	get_pwd(t_buildins *vars)
{
	if (vars->pwd != NULL)
	{
		vars->oldpwd = ft_strdup(vars->pwd);
		if (!vars->oldpwd)
		{
			perror(vars->oldpwd);
			exit(EXIT_FAILURE);
		}
	}
	vars->pwd = getcwd(vars->pwd, 0);
	if (!vars->pwd || access(vars->pwd, F_OK) == -1)
	{
		perror(vars->pwd);
		exit(EXIT_FAILURE);
	}
}

void	join_oldpwd(t_buildins *vars, char **temp, char *oldpwd)
{
	int		x;

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

void	get_oldpwd(t_buildins *vars)
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
