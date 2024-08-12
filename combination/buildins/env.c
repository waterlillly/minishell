/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbaumeis <lbaumeis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 12:54:57 by lbaumeis          #+#    #+#             */
/*   Updated: 2024/08/12 02:31:13 by lbaumeis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../exec.h"

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
