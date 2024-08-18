/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbaumeis <lbaumeis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 12:54:57 by lbaumeis          #+#    #+#             */
/*   Updated: 2024/08/17 14:37:58 by lbaumeis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	get_pwd(t_pipex *p)
{
	char	*temp;

	temp = NULL;
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
		return ;//error(p, "strdup or access", p->status);
	}
}

char	*get_env(t_pipex *p, char *str)
{
	int		x;
	size_t	len;
	char	*result;

	x = 0;
	len = 0;
	result = NULL;
	if (!str)
		return ("\n");
	while (p->menv[x])
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
		x++;
	}
	return ("\n");
}

void	get_menv(t_pipex *p, char **envp)
{
	int	x;

	x = 0;
	p->menv = malloc(sizeof(char *) * (ft_arrlen(envp) + 1));
	if (!p->menv)
		return ;//error(p, "malloc", p->status);
	while (envp[x])
	{
		p->menv[x] = ft_strdup(envp[x]);
		if (!p->menv[x])
			return ;//error(p, "strdup", p->status);
		x++;
	}
	if (x != ft_arrlen(envp))
		return ;//error(p, "menv", p->status);
	p->menv[x] = NULL;
}

int	backup_env(t_pipex *p)
{
	char	*temp;
	
	temp = NULL;
	p->xport = malloc(sizeof(char *) * 4);
	if (!p->xport)
		return (1);//error(p, "malloc", p->status);
	p->menv = malloc(sizeof(char *) * 3);
	if (!p->menv)
		return (1);//error(p, "malloc", p->status);
	temp = getcwd(temp, 0);
	if (!temp || access(temp, R_OK) != 0)
		return (err_free(p), 1);
	p->xport[0] = create_add_export("OLDPWD");
	if (!p->xport[0])
		return (ft_free_double(p->xport), ft_free_double(p->menv), err_free(p), 1);
	p->xport[1] = create_add_export(ft_strjoin("PWD=", temp));
	if (!p->xport[1])
		return (ft_free_double(p->xport), ft_free_double(p->menv), err_free(p), 1);
	p->xport[2] = create_add_export("SHLVL=1");
	if (!p->xport[2])
		return (ft_free_double(p->xport), ft_free_double(p->menv), err_free(p), 1);
	p->xport[3] = NULL;
	p->xport = resort_arr(p->xport);
	if (!p->xport)
		return (ft_free_double(p->xport), ft_free_double(p->menv), err_free(p), 1);
	p->menv[0] = ft_strjoin("PWD=", temp);
	if (!p->menv[0])
		return (ft_free_double(p->xport), ft_free_double(p->menv), err_free(p), 1);
	p->menv[1] = ft_strdup("SHLVL=1");
	if (!p->menv[1])
		return (ft_free_double(p->xport), ft_free_double(p->menv), err_free(p), 1);
	p->menv[2] = NULL;
	if (!p->menv)
		return (ft_free_double(p->xport), ft_free_double(p->menv), err_free(p), 1);
	return (0);
}
