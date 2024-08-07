/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   processes.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbaumeis <lbaumeis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 06:41:51 by lbaumeis          #+#    #+#             */
/*   Updated: 2024/08/07 14:22:40 by lbaumeis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	first(t_ms *ms, int *c)
{
	if (ms->e->here == true)
	{
		ms->e->filein = open("hd", O_RDONLY);
		if (ms->e->filein == -1 || access("hd", R_OK) == -1)
			error(ms, "hd", 1);
	}
	if (dup2(ms->e->filein, STDIN_FILENO) == -1)
		error(ms, "dup2 failed", 1);
	if (dup2(ms->e->pip[*c][1], STDOUT_FILENO) == -1)
		error(ms, "dup2 failed", 1);
	close_pipes(ms);
	exec_cmd(ms);
	error(ms, "exec_cmd failed", 1);
}
/*
void	first(t_ms *ms)
{
	if (ms->e->m->infile)
	{
		if (dup2(ms->e->filein, STDIN_FILENO) == -1)
			error(ms, NULL, 1);
	}
	if (dup2(ms->e->pip[ms->e->c][1], STDOUT_FILENO) == -1)
		error(ms, NULL, 1);
	close_pipes(ms->e);
	exec_cmd(ms->e);
	error(ms, NULL, 1);
}
*/

void	middle(t_ms *ms, int *c)
{
	if (dup2(ms->e->pip[*c - 1][0], STDIN_FILENO) == -1)
		error(ms, "dup2 failed", 1);
	if (dup2(ms->e->pip[*c][1], STDOUT_FILENO) == -1)
		error(ms, "dup2 failed", 1);
	close_pipes(ms);
	exec_cmd(ms);
	error(ms, "exec_cmd failed", 1);
}

void	last(t_ms *ms, int *c)
{
	if (dup2(ms->e->pip[*c - 1][0], STDIN_FILENO) == -1)
		error(ms, "dup2 failed", 1);
	if (ms->e->out == true)
	{
		if (dup2(ms->e->fileout, STDOUT_FILENO) == -1)
			error(ms, "dup2 failed", 1);
	}
	else
	{
		if (dup2(STDOUT_FILENO, ms->e->copy_stdout) == -1)
			error(ms, "dup2 failed", 1);
	}
	close_pipes(ms);
	exec_cmd(ms);
	error(ms, "exec_cmd failed", 1);
}

/*
void	last(t_ms *ms)
{
	if (dup2(ms->e->pip[ms->e->c - 1][0], STDIN_FILENO) == -1)
		error(ms, NULL, 1);
	if (ms->e->m->std_out == false)
	{
		if (dup2(ms->e->fileout, STDOUT_FILENO) == -1)
			error(ms, NULL, 1);
	}
	close_pipes(ms->e);
	exec_cmd(ms->e);
	error(ms, NULL, 1);
}
*/

void	do_child(t_ms *ms, int *c)
{
	if (*c == 0)
	{
		if (ms->e->cwd)
			no_infile_exec(ms, c);
		else
			first(ms, c);
	}
	else if (*c == ms->e->cmd_count - 1)
		last(ms, c);
	else
		middle(ms, c);
}
