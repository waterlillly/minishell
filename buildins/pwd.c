/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbaumeis <lbaumeis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/27 12:47:48 by lbaumeis          #+#    #+#             */
/*   Updated: 2024/10/03 15:55:33 by lbaumeis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	reset_old_pwd(t_pipex *p, char *path)
{
	if (!p || !path)
		return ;
	free(p->oldpwd);
	p->oldpwd = NULL;
	p->oldpwd = get_env(p, "PWD");
	if (!p->oldpwd)
		return ;
	free(p->pwd);
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
	int	x;
	int	z;

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
	return (update(p, "PWD", oldpwd), update(p, "OLDPWD", p->pwd),
		free(p->pwd), p->pwd = NULL, p->pwd = oldpwd, 1);
}

int	join_oldpwd(t_pipex *p, char **temp, char *oldpwd)
{
	int	x;
	int	y;
	int	z;

	x = 0;
	y = get_int(temp);
	z = ft_arrlen(temp) - 1;
	(void)z;
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
				return (update(p, "OLDPWD", p->pwd), update(p, "PWD", oldpwd), free(p->pwd),
					p->pwd = NULL, p->pwd = oldpwd, 1);
			}
			return (free(p->oldpwd), p->oldpwd = NULL, p->oldpwd = oldpwd,
				update(p, "PWD", oldpwd), update(p, "OLDPWD", p->oldpwd), 0);
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
