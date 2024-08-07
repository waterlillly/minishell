/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbaumeis <lbaumeis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 06:41:43 by lbaumeis          #+#    #+#             */
/*   Updated: 2024/08/07 14:21:46 by lbaumeis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*is_exec(t_ms *ms)
{
	int	i;

	i = 0;
	if (access(ms->e->cmd, X_OK) == 0)
		return (ms->e->cmd);
	while (ms->e->paths[i])
	{
		ms->e->executable = ft_strjoin(ms->e->paths[i], "/");
		if (!ms->e->executable)
			error(ms, "strjoin failed", 1);
		ms->e->part = ft_strjoin(ms->e->executable, ms->e->cmd);
		if (!ms->e->part)
			error(ms, "strjoin failed", 1);
		free(ms->e->executable);
		ms->e->executable = NULL;
		if (access(ms->e->part, X_OK) == 0)
			return (ms->e->part);
		free(ms->e->part);
		ms->e->part = NULL;
		i++;
	}
	error(ms, "command not found", 127);
	return (NULL);
}

void	find_path(t_ms *ms)
{
	//maybe need first part?
	//int		i;

	//i = 0;
	//while (ft_strnstr(ms->e->menv[i], "PATH", 4) == 0)
	//	i++;
	ms->e->paths = ft_split(ms->e->mpath + 5, ':');
	if (!ms->e->paths)
		error(ms, "strjoin failed", 1);
	ms->e->path = is_exec(ms);
}

void	exec_cmd(t_ms *ms)
{
	ms->e->args = ft_split(ms->e->av[ms->e->x], ' ');
	if (!ms->e->args)
		error(ms, "ft_split failed", 1);
	ms->e->cmd = ms->e->args[0];
	//ms->e->paths = ms->e->envp;
	//ms->e->path = is_exec(p);
	find_path(ms);
	execve(ms->e->path, ms->e->args, &ms->e->mpath);
	error(ms, "execve failed", 1);//127?
}
