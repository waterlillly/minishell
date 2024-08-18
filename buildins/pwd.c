/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbaumeis <lbaumeis@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/27 12:47:48 by lbaumeis          #+#    #+#             */
/*   Updated: 2024/08/18 17:45:55 by lbaumeis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	reset_old_pwd(t_pipex *p, char *path)
{
	char	*temp;

	temp = NULL;
	if (!p || !path)
		return ;
	temp = ft_strdup(p->oldpwd);
	if (!temp)
		return ;//error(p, "strdup or no p->oldpwd", p->status);
	free(p->oldpwd);
	p->oldpwd = NULL;
	p->oldpwd = ft_strdup(p->pwd);
	if (!p->oldpwd)
		return ;//error(p, p->oldpwd, p->status);
	if (is_access(path))
	{
		free(p->pwd);
		p->pwd = NULL;
		p->pwd = ft_strdup(path);
	}
	else
		p->oldpwd = ft_strdup(temp);
	update(p, "PWD", p->pwd);
	update(p, "OLDPWD", p->oldpwd);
}

int	join_oldpwd(t_pipex *p, char **temp, char *oldpwd)
{
	int	x;

	x = 0;
	if (!p || !temp || !oldpwd)
		return (1);
	while (temp[x])
	{
		if (!temp[x + 1])
		{
			free(temp[x]);
			temp[x] = NULL;
			p->oldpwd = ft_strjoin_free_one(oldpwd, NULL);
			if (!oldpwd)
				return (1);//error(p, "p->oldpwd", p->status);
			return (0);
		}
		oldpwd = ft_strjoin_free_one(oldpwd, "/");
		if (!oldpwd)
			return (1);//error(p, "oldpwd", p->status);
		oldpwd = ft_strjoin_free_both(oldpwd, temp[x]);
		if (!oldpwd)
			return (1);//error(p, "oldpwd", p->status);
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
	temp = ft_split(p->pwd, '/');
	if (!temp)
		return (1);//error(p, "temp", p->status);
	oldpwd = ft_strdup("");
	if (!oldpwd)
		return (1);//error(p, "strdup", p->status);
	return (join_oldpwd(p, temp, oldpwd));
}
