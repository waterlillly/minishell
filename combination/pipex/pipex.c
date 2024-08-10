/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbaumeis <lbaumeis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 06:41:43 by lbaumeis          #+#    #+#             */
/*   Updated: 2024/08/10 21:37:43 by lbaumeis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../exec.h"

char	*is_exec(t_pipex *p)
{
	int	i;

	i = 0;
	if (access(p->cmd, X_OK) == 0)
		return (p->cmd);
	while (p->paths[i])
	{
		p->executable = ft_strjoin(p->paths[i], "/");
		if (!p->executable)
			error(p, "strjoin failed", p->status);
		p->part = ft_strjoin(p->executable, p->cmd);
		free(p->executable);
		p->executable = NULL;
		if (!p->part)
			error(p, "strjoin failed", p->status);
		if (access(p->part, X_OK) == 0)
			return (p->part);
		free(p->part);
		p->part = NULL;
		i++;
	}
	error(p, "command not found", 127);
	return (0);
}

void	find_path(t_pipex *p)
{
	int		i;

	i = 0;
	while (ft_strnstr(p->menv[i], "PATH", 4) == 0)
		i++;
	p->paths = ft_split(p->mpath, ':');
	if (!p->paths)
		error(p, "ft_split failed", p->status);
	p->path = is_exec(p);
}

int	exec_cmd(t_pipex *p)
{
	p->args = ft_split(p->av[p->x], ' ');
	if (!p->args)
		error(p, "ft_split failed", p->status);
	if (p->args[0][0] == '$'
		&& valid_env(p, ft_substr(p->args[0], 1, ft_strlen(p->args[0]) - 1)))
		p->cmd = xpand(p, p->args, 0);
	else
		p->cmd = p->args[0];
	if (is_buildin(p->cmd))
	{
		do_this(p);
		return (p->status);
	}
	else
	{
		find_path(p);
		execve(p->path, p->args, p->menv);
		error(p, "execve failed", p->status);
	}
	return (p->status);
}
