/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbaumeis <lbaumeis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 12:54:57 by lbaumeis          #+#    #+#             */
/*   Updated: 2024/07/30 13:18:36 by lbaumeis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "buildins.h"

void	get_pwd(t_buildins *vars)
{
	char	*temp;

	temp = NULL;
	if (vars->pwd)
	{
		temp = ft_strdup(vars->pwd);
		if (!temp)
			err_or("strdup");
		free(vars->pwd);
		vars->pwd = NULL;
	}
	vars->pwd = getcwd(vars->pwd, 0);
	if (!vars->pwd || access(vars->pwd, F_OK) == -1)
	{
		vars->pwd = ft_strdup(temp);
		free(temp);
		temp = NULL;
		err_or("strdup or access");
	}
}

char	*get_env(t_buildins *vars, char *str)
{
	int		x;
	size_t	len;
	char	*result;

	x = 0;
	len = 0;
	result = NULL;
	while (vars->menv[x])
	{
		if (ft_strnstr(vars->menv[x], str, ft_strlen(str))
			== &(vars->menv[x][0]))
		{
			len = ft_strlen(vars->menv[x]) - ft_strlen(str);
			result = malloc(sizeof(char) * len);
			if (!result)
				return (NULL);
			result = ft_substr(vars->menv[x], ft_strlen(str) + 1, len - 1);
			if (!result)
				return (NULL);
			return (result);
		}
		x++;
	}
	return (NULL);
}

void	get_menv(t_buildins *vars)
{
	int	x;

	x = 0;
	vars->menv = malloc(sizeof(char *) * (ft_arrlen(vars->envp) + 1));
	if (!vars->menv)
		err_or("malloc");
	while (vars->envp[x])
	{
		vars->menv[x] = ft_strdup(vars->envp[x]);
		if (!vars->menv[x])
		{
			ft_free_double(vars->menv);
			err_or("strdup");
		}
		x++;
	}
	if (x != ft_arrlen(vars->envp))
	{
		ft_free_double(vars->menv);
		err_or("menv");
	}
	vars->menv[x] = NULL;
}
