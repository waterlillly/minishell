/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   processes.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbaumeis <lbaumeis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 06:41:51 by lbaumeis          #+#    #+#             */
/*   Updated: 2024/08/07 18:05:48 by lbaumeis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../exec.h"

void	first(t_pipex *p, int *c)
{
	if (p->here == true)
	{
		p->filein = open("hd", O_RDONLY);
		if (p->filein == -1 || access("hd", R_OK) == -1)
			error(p, "hd", p->status);
	}
	if (dup2(p->filein, STDIN_FILENO) == -1)
		error(p, "dup2 failed", p->status);
	if (dup2(p->pip[*c][1], STDOUT_FILENO) == -1)
		error(p, "dup2 failed", p->status);
	close_pipes(p);
	exec_cmd(p);
	error(p, "exec_cmd failed", p->status);
}
/*
void	first(t_pipex *p)
{
	if (p->m->infile)
	{
		if (dup2(p->filein, STDIN_FILENO) == -1)
			error(p, "error", p->status);
	}
	if (dup2(p->pip[p->c][1], STDOUT_FILENO) == -1)
		error(p, "error", p->status);
	close_pipes(p);
	exec_cmd(p);
	error(p, "error", p->status);
}
*/

void	middle(t_pipex *p, int *c)
{
	if (dup2(p->pip[*c - 1][0], STDIN_FILENO) == -1)
		error(p, "dup2 failed", p->status);
	if (dup2(p->pip[*c][1], STDOUT_FILENO) == -1)
		error(p, "dup2 failed", p->status);
	close_pipes(p);
	exec_cmd(p);
	error(p, "exec_cmd failed", p->status);
}

void	last(t_pipex *p, int *c)
{
	if (dup2(p->pip[*c - 1][0], STDIN_FILENO) == -1)
		error(p, "dup2 failed", p->status);
	if (p->out == true)
	{
		if (dup2(p->fileout, STDOUT_FILENO) == -1)
			error(p, "dup2 failed", p->status);
	}
	else
	{
		if (dup2(STDOUT_FILENO, p->copy_stdout) == -1)
			error(p, "dup2 failed", p->status);
	}
	close_pipes(p);
	exec_cmd(p);
	error(p, "exec_cmd failed", p->status);
}

/*
void	last(t_pipex *p)
{
	if (dup2(p->pip[p->c - 1][0], STDIN_FILENO) == -1)
		error(p, "error", p->status);
	if (p->m->std_out == false)
	{
		if (dup2(p->fileout, STDOUT_FILENO) == -1)
			error(p, "error", p->status);
	}
	close_pipes(p);
	exec_cmd(p);
	error(p, "error", p->status);
}
*/

void	do_child(t_pipex *p, int *c)
{
	if (*c == 0)
	{
		if (p->cwd)
			no_infile_exec(p, c);
		else
			first(p, c);
	}
	else if (*c == p->cmd_count - 1)
		last(p, c);
	else
		middle(p, c);
}
