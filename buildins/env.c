/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbaumeis <lbaumeis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 12:54:57 by lbaumeis          #+#    #+#             */
/*   Updated: 2024/08/21 16:11:46 by lbaumeis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	**copy_arr_env(t_pipex *p)
{
	int		x;
	char	**arr;

	x = 0;
	if (!p || !p->menv)
		return (NULL);
	arr = NULL;
	arr = ft_calloc((ft_arrlen(p->menv) + 1), sizeof(char *));
	if (!arr)
		return (NULL);
	while (p->menv[x])
	{
		arr[x] = strcpy_until(p->menv[x]);
		x++;
	}
	arr[x] = NULL;
	return (arr);
}

bool	valid_env(t_pipex *p, char *tok)
{
	int	x;
	int	y;

	x = 0;
	if (!p || !tok || !p->menv)
		return (false);
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
	size_t	len;
	char	*result;

	x = -1;
	len = 0;
	result = NULL;
	while (p && str && p->menv && p->menv[++x])
	{
		if (ft_strnstr(p->menv[x], str, ft_strlen(str))
			== &(p->menv[x][0]))
		{
			len = ft_strlen(p->menv[x]) - ft_strlen(str);
			if (len <= 0)
				return ("\n");
			//result = malloc(sizeof(char) * len);
			//if (!result)
			//	return (NULL);
			result = ft_substr(p->menv[x], ft_strlen(str) + 1, len - 1);
			if (!result)
				return (NULL);
			return (result);
		}
	}
	return ("\n");
}

int	get_menv(t_pipex *p, char **envp)
{
	int	x;

	x = 0;
	if (!p)
		return (1);
	if (!envp)
		return (backup(p));
	p->menv = NULL;
	p->menv = ft_calloc((ft_arrlen(envp) + 1), sizeof(char *));
	if (!p->menv)
		return (1);
	while (envp[x])
	{
		p->menv[x] = ft_strdup(envp[x]);
		if (!p->menv[x])
			return (ft_free_double(p->menv), 1);
		x++;
	}
	p->menv[x] = NULL;
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
