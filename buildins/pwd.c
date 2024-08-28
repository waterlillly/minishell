/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbaumeis <lbaumeis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/27 12:47:48 by lbaumeis          #+#    #+#             */
/*   Updated: 2024/08/28 13:46:38 by lbaumeis         ###   ########.fr       */
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

int	join_oldpwd(t_pipex *p, char **temp, char *oldpwd)
{
	int	x;

	x = 0;
	while (p && temp && temp[x] && oldpwd)
	{
		if (!temp[x + 1])
		{
			p->oldpwd = NULL;
			p->oldpwd = ft_strjoin_free_one(oldpwd, NULL);
			if (!p->oldpwd)
				return (free(temp[x]), temp[x] = NULL, 1);
			return (free(temp[x]), temp[x] = NULL, 0);
		}
		if (oldpwd && oldpwd[ft_strlen(oldpwd)] != '/')
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
