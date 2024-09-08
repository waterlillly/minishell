/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbaumeis <lbaumeis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 18:04:36 by lbaumeis          #+#    #+#             */
/*   Updated: 2024/09/08 14:31:32 by lbaumeis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	restore_fds(t_pipex *p)
{
	if (p->copy_stdin != -1)
	{
		//printf("before: copy in: %d stdin: %d\n", p->copy_stdin, STDIN_FILENO);
		if (dup2(p->copy_stdin, STDIN_FILENO) == -1)
			return (perror("dup2 copy_stdin"));
		//printf("after: copy in: %d stdin: %d\n\n", p->copy_stdin, STDIN_FILENO);
		if (close(p->copy_stdin) != 0)
			return (perror("close copy_stdin"));
	}
	if (p->copy_stdout != -1)
	{
		//printf("before: copy out: %d stdout: %d\n", p->copy_stdout, STDOUT_FILENO);
		if (dup2(p->copy_stdout, STDOUT_FILENO) == -1)
			return (perror("dup2 copy_stdout"));
		//printf("after: copy out: %d stdout: %d\n\n", p->copy_stdout, STDOUT_FILENO);
		if (close(p->copy_stdout) != 0)
			return (perror("close copy_stdout"));
	}
}

void	closing(t_pipex *p)
{
	int	i;

	i = 0;
	if (!p || p->cmd_count <= 1)
		return ;
	if (p && p->filein != -1)// && p->filein != STDIN_FILENO)
		close(p->filein);
	if (p && p->fileout != -1)// && p->fileout != STDOUT_FILENO)
		close(p->fileout);
	if (p && p->pip && p->pip[i])
	{
		while (i < p->cmd_count - 1 && p->pip[i])
		{
			if (p->pip[i][0] && p->pip[i][0] != -1)// && p->pip[i][0] != STDIN_FILENO)
				close(p->pip[i][0]);
			if (p->pip[i][1] && p->pip[i][1] != -1)// && p->pip[i][1] != STDOUT_FILENO)
				close(p->pip[i][1]);
			//free(p->pip[i]);
			i++;
		}
		//free(p->pip);
		//p->pip = 0;
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
		while (i < p->cmd_count - 1 && p->pip[i])
		{
			if (p->pip[i][0] && p->pip[i][0] != -1)// && p->pip[i][0] != STDIN_FILENO)
				close(p->pip[i][0]);
			if (p->pip[i][1] && p->pip[i][1] != -1)// && p->pip[i][1] != STDOUT_FILENO)
				close(p->pip[i][1]);
			free(p->pip[i]);
			i++;
		}
		free(p->pip);
		p->pip = 0;
	}
}

void	close_all(t_pipex *p)
{
	if (p && p->filein != -1)// && p->filein != STDIN_FILENO)
		close(p->filein);
	if (p && p->fileout != -1)// && p->fileout != STDOUT_FILENO)
		close(p->fileout);
	if (p && p->copy_stdin != -1)// && p->copy_stdin != STDIN_FILENO)
		close(p->copy_stdin);
	if (p && p->copy_stdout != -1)// && p->copy_stdout != STDOUT_FILENO)
		close(p->copy_stdout);
	if (p && p->pip)
		close_pipes(p);
}

void	err_free(t_pipex *p)
{
	close_all(p);
	if (p->pid)
	{
		free(p->pid);
		p->pid = NULL;
	}
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
	{
		free(p->here);
		p->here = NULL;
	}
}
