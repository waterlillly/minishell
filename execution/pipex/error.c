/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbaumeis <lbaumeis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 18:04:36 by lbaumeis          #+#    #+#             */
/*   Updated: 2024/08/03 14:11:31 by lbaumeis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	close_pipes(t_pipex *p)
{
	int	i;

	i = p->cmd_count - 1;
	while (i >= 0)
	{
		if (p->pip[i][0] && p->pip[i][0] != -1 && p->pip[i][0] != STDIN_FILENO)
			close(p->pip[i][0]);
		if (p->pip[i][1] && p->pip[i][1] != -1 && p->pip[i][0] != STDOUT_FILENO)
			close(p->pip[i][1]);
		free(p->pip[i]);
		p->pip[i] = NULL;
		i--;
	}
	free(p->pip);
	p->pip = NULL;
}

void	close_all(t_pipex *p)
{
	if (p->filein && p->filein != STDIN_FILENO && p->filein != -1)
		close(p->filein);
	if (p->fileout && p->fileout != STDOUT_FILENO && p->fileout != -1)
		close(p->fileout);
	if (p->copy_stdout && p->copy_stdout != STDOUT_FILENO && p->copy_stdout != -1)
		close(p->copy_stdout);
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
	if (p->pip || p->copy_stdout)
		close_all(p);
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
	if (p->here)
		unlink("hd");
	exit(exit_status);
}
