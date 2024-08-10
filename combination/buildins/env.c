/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbaumeis <lbaumeis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 12:54:57 by lbaumeis          #+#    #+#             */
/*   Updated: 2024/08/10 19:47:03 by lbaumeis         ###   ########.fr       */
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
			error(p, "strdup", p->status);
		free(p->pwd);
		p->pwd = NULL;
	}
	p->pwd = getcwd(p->pwd, 0);
	if (!p->pwd || access(p->pwd, F_OK) == -1)
	{
		p->pwd = ft_strdup(temp);
		free(temp);
		temp = NULL;
		error(p, "strdup or access", p->status);
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
	while (p->menv[x])
	{
		if (ft_strnstr(p->menv[x], str, ft_strlen(str))
			== &(p->menv[x][0]))
		{
			len = ft_strlen(p->menv[x]) - ft_strlen(str);
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
		error(p, "malloc", p->status);
	while (envp[x])
	{
		p->menv[x] = ft_strdup(envp[x]);
		if (!p->menv[x])
		{
			ft_free_double(p->menv);
			error(p, "strdup", p->status);
		}
		x++;
	}
	if (x != ft_arrlen(envp))
	{
		ft_free_double(p->menv);
		error(p, "menv", p->status);
	}
	p->menv[x] = NULL;
}
