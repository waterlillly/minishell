/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbaumeis <lbaumeis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/27 12:47:48 by lbaumeis          #+#    #+#             */
/*   Updated: 2024/08/07 14:07:16 by lbaumeis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	reset_old_pwd(t_ms *ms, char *path)
{
	char	*temp;

	temp = NULL;
	temp = ft_strdup(ms->e->oldpwd);
	if (!temp)
		error(ms, "strdup or no ms->e->oldpwd", 1);
	free(ms->e->oldpwd);
	ms->e->oldpwd = NULL;
	ms->e->oldpwd = ft_strdup(ms->e->pwd);
	if (!ms->e->oldpwd)
		error(ms, ms->e->oldpwd, 1);
	if (access(path, F_OK) == 0)
	{
		free(ms->e->pwd);
		ms->e->pwd = NULL;
		ms->e->pwd = ft_strdup(path);
		if (!ms->e->pwd)
			error(ms, "strdup", 1);
	}
	else
	{
		ms->e->oldpwd = ft_strdup(temp);
		error(ms, "access", 1);
	}
}

void	join_oldpwd(t_ms *ms, char **temp, char *oldpwd)
{
	int	x;

	x = 0;
	while (temp[x])
	{
		if (temp[x + 1] == NULL)
		{
			free(temp[x]);
			temp[x] = NULL;
			ms->e->oldpwd = ft_strjoin_free_one(oldpwd, NULL);
			if (!oldpwd)
				error(ms, "ms->e->oldpwd", 1);
			break ;
		}
		oldpwd = ft_strjoin_free_one(oldpwd, "/");
		if (!oldpwd)
			error(ms, "oldpwd", 1);
		oldpwd = ft_strjoin_free_both(oldpwd, temp[x]);
		if (!oldpwd)
			error(ms, "oldpwd", 1);
		x++;
	}
	temp = NULL;
}

void	go_up_oldpwd(t_ms *ms)
{
	char	**temp;
	char	*oldpwd;

	temp = NULL;
	oldpwd = NULL;
	if (!ms->e->pwd)
		get_pwd(ms);
	temp = ft_split(ms->e->pwd, '/');
	if (!temp)
		error(ms, "temp", 1);
	oldpwd = ft_strdup("");
	if (!oldpwd)
		error(ms, "strdup", 1);
	join_oldpwd(ms, temp, oldpwd);
}
