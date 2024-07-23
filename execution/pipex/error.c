/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbaumeis <lbaumeis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 18:04:36 by lbaumeis          #+#    #+#             */
/*   Updated: 2024/07/23 18:03:02 by lbaumeis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	close_pipes(t_pipex *p)
{
	int	i;

	i = 0;
	while (i < p->cmd_count)
	{
		if (p->pip[i][0] && p->pip[i][0] != -1)
			close(p->pip[i][0]);
		if (p->pip[i][1] && p->pip[i][1] != -1)
			close(p->pip[i][1]);
		i++;
	}
}

void	close_all(t_pipex *p)
{
	if (p->filein && p->filein != STDIN_FILENO && p->filein != -1)
		close(p->filein);
	if (p->fileout && p->fileout != STDOUT_FILENO && p->fileout != -1)
		close(p->fileout);
	if (p->pip)
		close_pipes(p);
}

void	free_double(char **str)
{
	int	i;

	i = 0;
	if (!str)
		return ;
	while (str[i])
	{
		free(str[i]);
		str[i] = NULL;
		i++;
	}
	free(str);
	str = NULL;
}

void	err_free_two(t_pipex *p)
{
	if (p->pid)
	{
		free(p->pid);
		p->pid = NULL;
	}
	if (p->pip)
	{
		close_all(p);
		free(p->pip);
		p->pip = 0;
	}
	if (p->args)
	{
		free_double(p->args);
		p->args = NULL;
	}
	if (p->paths)
	{
		free_double(p->paths);
		p->paths = NULL;
	}
}

void	err_free(t_pipex *p, int exit_status)
{
	err_free_two(p);
	if (p->path)
	{
		free(p->path);
		p->path = NULL;
	}
	if (p->executable)
	{
		free(p->executable);
		p->executable = NULL;
	}
	if (p->part)
	{
		free(p->part);
		p->part = NULL;
	}
	if (p->copy_stdout)
		close(p->copy_stdout);
	exit(exit_status);
}
