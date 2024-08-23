/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbaumeis <lbaumeis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 18:04:36 by lbaumeis          #+#    #+#             */
/*   Updated: 2024/08/23 15:08:05 by lbaumeis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	restore_fds(t_pipex *p)
{
	if (p && p->copy_stdin != -1)
	{
		dup2(p->copy_stdin, STDIN_FILENO);
		close(p->copy_stdin);
	}
	if (p && p->copy_stdout != -1)
	{
		dup2(p->copy_stdout, STDOUT_FILENO);
		close(p->copy_stdout);
	}
}

void	close_pipes(t_pipex *p)
{
	int	i;

	i = 0;
	if (!p || p->cmd_count <= 1)
		return ;
	else if (p && p->pip && p->pip[i])
	{
		while (p->pip && i < (p->cmd_count - 1) && p->pip[i])
		{
			if (p->pip[i][0] && p->pip[i][0] != -1 && p->pip[i][0] != STDIN_FILENO)
				close(p->pip[i][0]);
			if (p->pip[i][1] && p->pip[i][1] != -1 && p->pip[i][1] != STDOUT_FILENO)
				close(p->pip[i][1]);
			free(p->pip[i]);
			p->pip[i] = 0;
			i++;
		}
		free(p->pip);
		p->pip = 0;
	}
}

void	close_all(t_pipex *p)
{
	if (p && p->filein && p->filein != STDIN_FILENO && p->filein != -1)
		close(p->filein);
	if (p && p->fileout && p->fileout != STDOUT_FILENO && p->fileout != -1)
		close(p->fileout);
	if (p && p->pip)
		close_pipes(p);
}

void	err_free_two(t_pipex *p)
{
	if (p->pid)
	{
		free(p->pid);
		p->pid = NULL;
	}
	if (p->pip || p->copy_stdout || p->copy_stdin)
		close_all(p);
}

void	err_free(t_pipex *p)
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
}
