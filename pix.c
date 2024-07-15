/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pix.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbaumeis <lbaumeis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 14:39:11 by lbaumeis          #+#    #+#             */
/*   Updated: 2024/07/15 19:17:47 by lbaumeis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void    close_all(t_pipex *p)
{
	if (p->filein)
		close_file(p->filein);
	if (p->fileout)
		close_file(p->fileout);
	if (p->pid)
		close_pid(p);
}

void	do_child(t_pipex *p, char **envp)
{
	decide(p);
	close_file(p->filein);
	close_file(p->fileout);
	close_pipe(p->pip[p->c]);
	printf("cmd_nbr: %d\n", p->x);
	exec_cmd(p->av, p->x, p, envp);
	err_free(p, 1);
}

void	decide(t_pipex *p)
{
	if (p->c == 0)
	{
		if (dup2(p->filein, STDIN_FILENO) == -1)
			err_free(p, 1);
		if (dup2(p->pip[p->c][1], STDOUT_FILENO) == -1)
			err_free(p, 1);
	}
	else if (p->c == p->cmd_count - 1)
	{
		if (dup2(p->pip[p->c - 1][0], STDIN_FILENO) == -1)
			err_free(p, 1);
		if (dup2(p->fileout, STDOUT_FILENO) == -1)
			err_free(p, 1);
		p->x++;
	}
	else//middle p->c < p->cmd_count + 2
	{
		if (dup2(p->pip[p->c - 1][0], STDIN_FILENO) == -1)
			err_free(p, 1);
		if (dup2(p->pip[p->c][1], STDOUT_FILENO) == -1)
			err_free(p, 1);
		p->x++;
	}
}

void	processes(t_pipex *p, char **envp)
{
	while (p->c < p->cmd_count)
	{
		p->pid[p->c] = fork();
		if (p->pid[p->c] == -1)
			err_free(p, 1);
		if (p->pid[p->c] == 0)
			do_child(p, envp);
		close_all(p);
		printf("process: %d\n", p->c);
		p->c++;
	}
}

/*
void	do_child(t_pipex *p, int *pipe_fd, int filein_fd, char **envp)
{
	if (p->c < p->cmd_count - 1)
		close(pipe_fd[0]);
	if (filein_fd != -1)
	{
		dup2(filein_fd, STDIN_FILENO);
		close(filein_fd);
	}
	if (pipe_fd[1] != p->fileout)
	{
		dup2(pipe_fd[1], STDOUT_FILENO);
		close(pipe_fd[1]);
	}
	exec_cmd(p->av, p->c + 2, p, envp);
}

void	do_else(t_pipex *p, int *pipe_fd, int filein_fd)
{
	if (filein_fd != -1)
		close(filein_fd);
	if (pipe_fd[1] != p->fileout)
		close(pipe_fd[1]);
	filein_fd = pipe_fd[0];
}

void	start(t_pipex *p, char **envp)
{
    int		pipe_fd[2];
	int		filein_fd;

	filein_fd = p->filein;
	while (p->c < p->cmd_count)
	{
		if (p->c < p->cmd_count - 1)
		{
			if (pipe(pipe_fd) == -1)
				err_free(p, NULL, NULL, 1);
		}
		else
		{
			pipe_fd[0] = -1;
			pipe_fd[1] = p->fileout;
		}
		p->pid[p->c] = fork();
		if (p->pid[p->c] == -1)
			err_free(p, pipe_fd, NULL, 1);
		else if (p->pid[p->c] == 0)
			do_child(p, pipe_fd, filein_fd, envp);
		else
			do_else(p, pipe_fd, filein_fd);
		p->c++;
	}
	if (filein_fd != -1)
		close(filein_fd);
}
*/