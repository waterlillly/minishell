/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mehras <mehras@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 12:54:57 by lbaumeis          #+#    #+#             */
/*   Updated: 2024/08/27 19:04:26 by mehras           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	**copy_arr_env(t_pipex *p)
{
	int		x;
	char	**arr;
	char	*temp;

	x = 0;
	if (!p || !p->menv)
		return (NULL);
	arr = ft_calloc((ft_arrlen(p->menv) + 1), sizeof(char *));
	if (!arr)
		return (NULL);
	while (p->menv[x])
	{
		temp = strcpy_until(p->menv[x]);
		if (!temp)
			return (ft_free_double(arr), NULL);
		arr[x] = temp;
		if (!arr[x])
			return (ft_free_double(arr), NULL);
		x++;
	}
	return (arr);
}

bool	valid_env(t_pipex *p, char *tok)
{
	int	x;
	int	y;

	x = 0;
	while (p->menv[x])
	{
		y = 0;
		while (tok[y] && p->menv[x][y] && tok[y] != '='
			&& tok[y] != '\0' && p->menv[x][y] != '=')
		{
			if (tok[y] == p->menv[x][y])
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

	x = -1;
	len = 0;
	while (p && str && p->menv && p->menv[++x])
	{
		if (ft_strlen(str) > 0 && ft_strlen(p->menv[x]) > 0
			&& ft_strnstr(p->menv[x], str, ft_strlen(str)) == &(p->menv[x][0]))
		{
			len = ft_strlen(p->menv[x]) - ft_strlen(str);
			if (len <= 0)
				break ;
			res = ft_substr(p->menv[x], ft_strlen(str) + 1, (size_t)len + 1);
			if (!res)
				return (NULL);
			return (res);
		}
	}
	return ("\n");
}

int	get_menv(t_pipex *p, char **envp)
{
	int	x;

	x = 0;
	//if (!envp)
	//	return (backup(p));
	p->menv = (char **)ft_calloc((ft_strlen_2d(envp) + 1), sizeof(char *));
	if (!p->menv)
		return (1);
	while (envp[x])
	{
		p->menv[x] = envp[x];
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
	x = combine_export(p);
	return (x);
}