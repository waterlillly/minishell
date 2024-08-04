/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_find_path.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbaumeis <lbaumeis@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 13:26:28 by lbaumeis          #+#    #+#             */
/*   Updated: 2024/08/04 20:06:01 by lbaumeis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "buildins.h"

int	add_to_path(t_buildins *vars, char *t)
{
	char	*temp;
	char	*new;

	temp = NULL;
	new = NULL;
	temp = ft_strjoin(vars->pwd, "/");
	if (!temp)
		err_or(temp);
	new = ft_strjoin_free_one(temp, t);
	//if (!new)
	//	err_or(temp);
	//if (access(new, X_OK) == 0)
	//	return (err_or("access"), 1);
	if (new && is_access(new))
	{
		reset_old_pwd(vars, new);
		return (chdir(new));
	}
	return (err_or(new), 1);
}

int	go_back(t_buildins *vars, int print)
{
	char	*temp;

	temp = NULL;
	temp = ft_strdup(vars->oldpwd);
	if (!temp)
		err_or(temp);
	if (is_access(temp))
	{
		reset_old_pwd(vars, temp);
		if (print == 1)
			printf("%s\n", vars->oldpwd);
		return (chdir(temp));
	}
	return (err_or(temp), 1);
}

char	*check_slash(char *tok, char *temp)
{
	int	x;

	x = 0;
	while (tok[x])
	{
		if (tok[x] == '/')
			x++;
		else
			return (err_or("no such file or directory"), NULL);
	}
	if (x > 2)
	{
		temp = ft_strdup("/");
		if (!temp)
			err_or(temp);
		return (temp);
	}
	else
		return (tok);
}

int	go_slash(t_buildins *vars, char **token, int x)
{
	char	*temp;

	temp = NULL;
	if ((token[x + 1][1] == '/' && token[x + 1][2] == '\0')
		|| (token[x + 1][1] == '\0'
		|| (token[x + 1][1] == '/' && token[x + 1][2] == '/')))
	{
		temp = check_slash(token[x + 1], temp);
		if (!temp)
			err_or(temp);
		if (is_access(temp))
		{
			reset_old_pwd(vars, temp);
			return (chdir(token[x + 1]));
		}
	}
	return (err_or(token[x + 1]), 1);
}

int	go_full_path(t_buildins *vars, char **token, int x)
{
	if (is_access(token[x + 1]) == true)
	{
		reset_old_pwd(vars, token[x + 1]);
		return (chdir(token[x + 1]));
	}
	return (err_or(token[x + 1]), 1);
}
