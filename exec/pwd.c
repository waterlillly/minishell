/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbaumeis <lbaumeis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/27 12:47:48 by lbaumeis          #+#    #+#             */
/*   Updated: 2024/10/05 20:32:18 by lbaumeis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	reset_old_pwd(t_pipex *p, char *path)
{
	char	**new;

	new = NULL;
	if (!p || !path)
		return ;
	p->oldpwd = NULL;
	if (!get_env(p, "PWD"))
	{
		if (!p->pwd)
			p->pwd = get_env(p, "HOME");
		new = ft_calloc(3, sizeof(char *));
		if (!new)
			return ;
		new[0] = "";
		new[1] = ft_strjoin("PWD=", p->pwd);
		set_export(p, new);
		ft_free_double(new);
		update(p, "PWD", p->pwd);
	}
	p->oldpwd = get_env(p, "PWD");
	if (!p->oldpwd)
		return ;
	p->pwd = NULL;
	p->pwd = ft_strdup(path);
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

int	going_back(char *oldpwd, t_pipex *p, int y, char **temp)
{
	int		x;
	int		z;
	char	*err;

	x = 0;
	z = ft_arrlen(temp) - 1;
	while (p && temp[x] && x < (z - (y * 2)))
	{
		if (oldpwd[ft_strlen(oldpwd) - 1] != '/')
			oldpwd = ft_strjoin_free_one(oldpwd, "/");
		oldpwd = ft_strjoin_free_one(oldpwd, temp[x]);
		x++;
	}
	if (x == (z - (y * 2)) && is_access(oldpwd))
		return (free(p->oldpwd), p->oldpwd = NULL, p->oldpwd = oldpwd, 0);
	while (temp[x])
	{
		if (oldpwd[ft_strlen(oldpwd) - 1] != '/')
			oldpwd = ft_strjoin_free_one(oldpwd, "/");
		oldpwd = ft_strjoin_free_one(oldpwd, temp[x]);
		x++;
	}
	oldpwd = ft_strjoin_free_one(oldpwd, "/..");
	err = ft_strjoin("cd: ", oldpwd);
	return (perror(err), free(err), err = NULL, free(p->oldpwd),
		p->oldpwd = NULL, p->oldpwd = ft_strdup(p->pwd),
		free(p->pwd), p->pwd = NULL, p->pwd = oldpwd, 1);
}

int	join_oldpwd(t_pipex *p, char **temp, char *oldpwd)
{
	int	x;
	int	y;

	x = 0;
	y = get_int(temp);
	if (p && temp[x] && y > 0)
		return (going_back(oldpwd, p, y, temp));
	while (p && temp[x])
	{
		if (!temp[x + 1])
		{
			if (!is_access(oldpwd))
			{
				oldpwd = ft_strjoin_free_one(oldpwd, "/");
				oldpwd = ft_strjoin_free_one(oldpwd, temp[x]);
				oldpwd = ft_strjoin_free_one(oldpwd, "/..");
				return (perror(oldpwd), free(p->oldpwd), p->oldpwd = NULL,
					p->oldpwd = ft_strdup(p->pwd), free(p->pwd), p->pwd = NULL, p->pwd = oldpwd, 1);
			}
			return (free(p->oldpwd), p->oldpwd = NULL, p->oldpwd = oldpwd,
				update(p, "OLDPWD", p->oldpwd), 0);
		}
		if (oldpwd && ft_strlen(oldpwd) > 0 && oldpwd[ft_strlen(oldpwd) - 1] != '/')
			oldpwd = ft_strjoin_free_one(oldpwd, "/");
		oldpwd = ft_strjoin_free_one(oldpwd, temp[x]);
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
		get_env(p, "PWD");
		if (!p->pwd)
			return (1);
	}
	if (ft_strcmp_bool(p->pwd, "/"))
		return (0);
	temp = ft_split(p->pwd, '/');
	if (!temp)
		return (1);
	oldpwd = ft_strdup("/");
	if (!oldpwd)
		return (1);
	return (join_oldpwd(p, temp, oldpwd));
}
