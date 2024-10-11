/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbaumeis <lbaumeis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 12:54:57 by lbaumeis          #+#    #+#             */
/*   Updated: 2024/10/11 19:16:25 by lbaumeis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	copy_arr_env(t_pipex *p, char **arr)
{
	int		x;
	char	*temp;

	x = 0;
	if (!p || !p->menv || !arr)
		return ;
	while (p->menv[x])
	{
		temp = NULL;
		temp = strcpy_until(p->menv[x]);
		if (!temp)
			return (ft_free_double(arr));
		arr[x] = ft_strdup(temp);
		free(temp);
		if (!arr[x])
			return (ft_free_double(arr));
		x++;
	}
}

bool	valid_env(t_pipex *p, char *tok)
{
	int	x;
	int	y;

	x = 0;
	if (!p || !tok)
		return (false);
	while (p->menv[x])
	{
		y = 0;
		while (tok[y] && p->menv[x][y])
		{
			if (tok[y] == p->menv[x][y] && (tok[y] != '=' && p->menv[x][y] != '='))
				y++;
			else
				break ;
		}
		if ((tok[y] == '=' || tok[y] == '\0') && p->menv[x][y] == '=')
			return (true);
		x++;
	}
	return (false);
}

char	*get_env(t_pipex *p, char *str)
{
	int		x;
	int		len;
	char	*res;

	x = 0;
	len = 0;
	if (!p || !str || !p->menv)
		return (NULL);
	while (p->menv[x])
	{
		if (ft_strlen(str) > 0 && ft_strlen(p->menv[x]) > 0
			&& ft_strnstr(p->menv[x], str, ft_strlen(str)) == &(p->menv[x][0]))
		{
			len = ft_strlen(p->menv[x]) - ft_strlen(str);
			if (len <= 0)
				break ;
			res = ft_substr(p->menv[x], ft_strlen(str) + 1, (size_t)len + 1);
			return (res);
		}
		x++;
	}
	return ("\n");
}

int	get_menv(t_pipex *p, char **envp)
{
	int	x;

	x = 0;
	p->menv = (char **)ft_calloc((ft_arrlen(envp) + 1), sizeof(char *));
	if (!p->menv)
		return (1);
	while (envp[x])
	{
		p->menv[x] = ft_strdup(envp[x]);
		if (!p->menv[x])
			return (1);
		x++;
	}
	return (0);
}

int	buildins_init(t_pipex *p, char **envp)
{
	int	x;

	x = 0;
	x = get_menv(p, envp);
	if (x != 0)
		return (x);
	p->pwd = get_env(p, "PWD");
	if (!p->pwd)
		return (1);
	p->oldpwd = get_env(p, "OLDPWD");
	if (!p->oldpwd)
		return (1);
	p->home = get_env(p, "HOME");
	if (!p->home)
		return (1);
	p->mpath = get_env(p, "PATH");
	if (!p->mpath)
		return (1);
	return (combine_export(p));
}
