/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbaumeis <lbaumeis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 12:54:57 by lbaumeis          #+#    #+#             */
/*   Updated: 2024/08/07 15:41:10 by lbaumeis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	get_pwd(t_ms *ms)
{
	char	*temp;

	temp = NULL;
	if (ms->e->pwd)
	{
		temp = ft_strdup(ms->e->pwd);
		if (!temp)
			error(ms, "strdup", 1);
		free(ms->e->pwd);
		ms->e->pwd = NULL;
	}
	ms->e->pwd = getcwd(ms->e->pwd, 0);
	if (!ms->e->pwd || access(ms->e->pwd, F_OK) == -1)
	{
		ms->e->pwd = ft_strdup(temp);
		free(temp);
		temp = NULL;
		error(ms, "strdup or access", 1);
	}
}

char	*get_env(t_ms *ms, char *str)
{
	int		x;
	size_t	len;
	char	*result;

	x = 0;
	len = 0;
	result = NULL;
	while (ms->e->menv[x])
	{
		if (ft_strnstr(ms->e->menv[x], str, ft_strlen(str))
			== &(ms->e->menv[x][0]))
		{
			len = ft_strlen(ms->e->menv[x]) - ft_strlen(str);
			result = malloc(sizeof(char) * len);
			if (!result)
				return ("\n");
			result = ft_substr(ms->e->menv[x], ft_strlen(str) + 1, len - 1);
			if (!result)
				return ("\n");
			return (result);
		}
		x++;
	}
	return ("\n");
}

void	get_menv(t_ms *ms, char **envp)
{
	int	x;

	x = 0;
	ms->e->menv = malloc(sizeof(char *) * (ft_arrlen(envp) + 1));
	if (!ms->e->menv)
		error(ms, "malloc", 1);
	while (envp[x])
	{
		ms->e->menv[x] = ft_strdup(envp[x]);
		if (!ms->e->menv[x])
		{
			ft_free_double(ms->e->menv);
			error(ms, "strdup", 1);
		}
		x++;
	}
	if (x != ft_arrlen(envp))
	{
		ft_free_double(ms->e->menv);
		error(ms, "menv", 1);
	}
	ms->e->menv[x] = NULL;
}
