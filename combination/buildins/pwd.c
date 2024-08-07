/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbaumeis <lbaumeis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/27 12:47:48 by lbaumeis          #+#    #+#             */
/*   Updated: 2024/08/07 18:57:47 by lbaumeis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../exec.h"

void	reset_old_pwd(t_pipex *p, char *path)
{
	char	*temp;

	temp = NULL;
	temp = ft_strdup(p->oldpwd);
	if (!temp)
		error(p, "strdup or no p->oldpwd", p->status);
	free(p->oldpwd);
	p->oldpwd = NULL;
	p->oldpwd = ft_strdup(p->pwd);
	if (!p->oldpwd)
		error(p, p->oldpwd, p->status);
	if (access(path, F_OK) == 0)
	{
		free(p->pwd);
		p->pwd = NULL;
		p->pwd = ft_strdup(path);
		if (!p->pwd)
			error(p, "strdup", p->status);
	}
	else
	{
		p->oldpwd = ft_strdup(temp);
		error(p, "access", p->status);
	}
}

void	join_oldpwd(t_pipex *p, char **temp, char *oldpwd)
{
	int	x;

	x = 0;
	while (temp[x])
	{
		if (temp[x + 1] == NULL)
		{
			free(temp[x]);
			temp[x] = NULL;
			p->oldpwd = ft_strjoin_free_one(oldpwd, NULL);
			if (!oldpwd)
				error(p, "p->oldpwd", p->status);
			break ;
		}
		oldpwd = ft_strjoin_free_one(oldpwd, "/");
		if (!oldpwd)
			error(p, "oldpwd", p->status);
		oldpwd = ft_strjoin_free_both(oldpwd, temp[x]);
		if (!oldpwd)
			error(p, "oldpwd", p->status);
		x++;
	}
	temp = NULL;
}

void	go_up_oldpwd(t_pipex *p)
{
	char	**temp;
	char	*oldpwd;

	temp = NULL;
	oldpwd = NULL;
	if (!p->pwd)
		get_pwd(p);
	temp = ft_split(p->pwd, '/');
	if (!temp)
		error(p, "temp", p->status);
	oldpwd = ft_strdup("");
	if (!oldpwd)
		error(p, "strdup", p->status);
	join_oldpwd(p, temp, oldpwd);
}
