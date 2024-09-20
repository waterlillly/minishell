/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbaumeis <lbaumeis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/27 12:47:48 by lbaumeis          #+#    #+#             */
/*   Updated: 2024/09/20 20:37:00 by lbaumeis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	reset_old_pwd(t_pipex *p, char *path)
{
	char	*temp;

	temp = NULL;
	temp = ft_strdup(p->oldpwd);
	if (!temp)
		return ;
	free(p->oldpwd);
	p->oldpwd = NULL;
	p->oldpwd = ft_strdup(p->pwd);
	if (!p->oldpwd)
		return ;
	if (is_access(path))
	{
		free(p->pwd);
		p->pwd = NULL;
		p->pwd = ft_strdup(path);
	}
	else
	{
		free(p->oldpwd);
		p->oldpwd = NULL;
		p->oldpwd = ft_strdup(temp);
	}
	free(temp);
	temp = NULL;
}

int	get_int(char **temp)
{
	int	x;
	int	i;

	x = 0;
	i = 0;
	while (temp[x])
	{
		if (ft_strcmp_bool(temp[x], ".."))
			i++;
		x++;
	}
	return (i);
}

int	join_oldpwd(t_pipex *p, char **temp, char *oldpwd)
{
	int	x;
	int	y;
	int	z;

	x = 0;
	y = get_int(temp);
	z = ft_arrlen(temp) - 1;
	ft_print_array(temp);
	if (y > 0)
		y *= 2;
	while (p && temp[x] && oldpwd)
	{
		if (x == (z - y) && temp[x])
		{
			p->oldpwd = NULL;
			if (is_access(oldpwd))
				return (p->oldpwd = oldpwd, update(p, "PWD", p->oldpwd), 0);
			oldpwd = ft_strjoin_free_one(oldpwd, "/");
			p->oldpwd = ft_strjoin_free_both(oldpwd, temp[x]);
			if (!is_access(p->oldpwd))
				p->oldpwd = ft_strjoin_free_one(p->oldpwd, "/..");
			return (update(p, "PWD", p->oldpwd), 0);
		}
		if (oldpwd && oldpwd[ft_strlen(oldpwd) - 1] != '/')
		{
			oldpwd = ft_strjoin_free_one(oldpwd, "/");
			if (!oldpwd)
				return (1);
		}
		oldpwd = ft_strjoin_free_both(oldpwd, temp[x]);
		if (!oldpwd)
			return (1);
		x++;
	}
	return (1);
}

int	go_up_oldpwd(t_pipex *p)
{
	char	**temp;
	char	*oldpwd;

	temp = NULL;
	oldpwd = NULL;
	if (!p)
		return (1);
	if (!p->pwd)
	{
		p->pwd = NULL;
		p->pwd = get_env(p, "PWD");
		if (!p->pwd)
			return (1);
	}
	if (ft_strcmp_bool(p->pwd, "/"))
		return (0);
	temp = ft_split(p->pwd, '/');
	if (!temp)
		return (1);
	oldpwd = ft_strdup("");
	if (!oldpwd)
		return (1);
	return (join_oldpwd(p, temp, oldpwd));
}
