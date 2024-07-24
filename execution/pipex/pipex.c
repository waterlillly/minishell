/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbaumeis <lbaumeis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 06:41:43 by lbaumeis          #+#    #+#             */
/*   Updated: 2024/07/24 15:29:54 by lbaumeis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

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
			err_free(p, 1);
		p->part = ft_strjoin(p->executable, p->cmd);
		if (!p->part)
			err_free(p, 1);
		free(p->executable);
		p->executable = NULL;
		if (access(p->part, X_OK) == 0)
			return (p->part);
		free(p->part);
		p->part = NULL;
		i++;
	}
	ft_putendl_fd("Command not found", 2);
	err_free(p, 127);
	return (0);
}

void	find_path(t_pipex *p)
{
	int		i;

	i = 0;
	while (ft_strnstr(p->envp[i], "PATH", 4) == 0)
		i++;
	p->paths = ft_split(p->envp[i] + 5, ':');
	if (!p->paths)
		err_free(p, 1);
	p->path = is_exec(p);
}

void	exec_cmd(t_pipex *p)
{
	p->args = ft_split(p->av[p->x], ' ');
	if (!p->args)
		err_free(p, 1);
	p->cmd = p->args[0];
	find_path(p);
	execve(p->path, p->args, p->envp);
	perror("Execve");
	err_free(p, 1);
}
