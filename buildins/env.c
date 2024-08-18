/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbaumeis <lbaumeis@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 12:54:57 by lbaumeis          #+#    #+#             */
/*   Updated: 2024/08/18 16:50:15 by lbaumeis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
/*
void	get_pwd(t_pipex *p)
{
	char	*temp;

	temp = NULL;
	if (!p)
		return ;
	if (p->pwd)
	{
		temp = ft_strdup(p->pwd);
		if (!temp)
			return ;//error(p, "strdup", p->status);
		free(p->pwd);
		p->pwd = NULL;
	}
	p->pwd = get_env(p, "PWD");
	if (!p->pwd || access(p->pwd, F_OK) == -1)
	{
		p->pwd = ft_strdup(temp);
		free(temp);
		temp = NULL;
		return ;
	}
}
*/

char	**copy_arr_env(t_pipex *p)
{
	int		x;
	char	**arr;

	x = 0;
	if (!p || !p->menv)
		return (NULL);
	arr = NULL;
	arr = malloc(sizeof(char *) * (ft_arrlen(p->menv) + 1));
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
			result = malloc(sizeof(char) * len);
			if (!result)
				return (NULL);
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
	p->menv = malloc(sizeof(char *) * (ft_arrlen(envp) + 1));
	if (!p->menv)
		return (1);
	while (envp[x])
	{
		p->menv[x] = ft_strdup(envp[x]);
		if (!p->menv[x])
			return (1);
		x++;
	}
	p->menv[x] = NULL;
	return (0);
}

int	buildins_init(t_pipex *p, char **envp)
{
	get_menv(p, envp);
	p->pwd = get_env(p, "PWD");
	go_up_oldpwd(p);
	p->home = get_env(p, "HOME");
	if (!p->home)
		return (err_free(p), 1);
	p->mpath = get_env(p, "PATH");
	if (!p->home)
		return (err_free(p), 1);
	return (combine_export(p));
}
