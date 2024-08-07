/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbaumeis <lbaumeis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 06:41:58 by lbaumeis          #+#    #+#             */
/*   Updated: 2024/08/07 12:46:44 by lbaumeis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	check_filein(t_ms *ms)
{
	char	*str;

	str = NULL;
	ms->e->filein = -1;
	if (!ms->e->delimiter && !ms->e->cwd)
	{
		ms->e->filein = open(ms->e->av[1], O_RDONLY, 0644);
		if (ms->e->filein == -1 || access(ms->e->av[1], R_OK) == -1)
			error(ms, ms->e->av[1], 1);
	}
}

void	check_fileout(t_ms *ms)
{
	int	x;

	x = ms->e->x + ms->e->cmd_count;
	ms->e->fileout = open(ms->e->av[x], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (ms->e->fileout == -1 || access(ms->e->av[x], W_OK) == -1)
		error(ms, ms->e->av[x], 1);
}

void init_pipes(t_ms *ms)
{
	int i;

	i = 0;
    ms->e->pip = malloc(ms->e->cmd_count * sizeof(int *));
	if (!ms->e->pip)
		error(ms, "malloc failed", 1);
    while (i < ms->e->cmd_count && ms->e->cmd_count > 1)
	{
        ms->e->pip[i] = malloc(sizeof(int) * 2);
		if (!ms->e->pip[i])
			error(ms, "malloc failed", 1);
        if (pipe(ms->e->pip[i]) == -1)
			error(ms, "pipe failed", 1);
		i++;
    }
}

/*
void	check_in(t_ms *ms)
{
	if (ms->e->m->infile)
	{
		ms->e->filein = open(ms->e->m->infile, O_RDONLY, 0644);
		if (ms->e->filein == -1)
		{
			perror(ms->e->av[1]);
			error(ms, NULL, 1);
		}
		if (access(ms->e->m->infile, F_OK) == -1)
		{
			perror(ms->e->m->infile);
			error(ms, NULL, 1);
		}
	}
}

void	check_out(t_ms *ms)
{
	if (ms->e->m->out == false)//need an outfile!
	{
		ms->e->fileout = open(ms->e->m->outfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (ms->e->fileout == -1)
		{
			perror(ms->e->m->outfile);
			error(ms, NULL, 1);
		}
		if (access(ms->e->m->outfile, W_OK) == -1)
		{
			perror(ms->e->m->outfile);
			error(ms, NULL, 1);
		}
	}
}


void	init_p(t_ms *ms, t_buildins *vars)
{
	ms->e->vars = vars;
	ms->e->envp = vars->menv;
	ms->e->cwd = NULL;
	ms->e->copy_stdout = dup(STDOUT_FILENO);
	if (ms->e->copy_stdout == -1)
		error(ms, NULL, 1);
	ms->e->in = false;
	ms->e->out = true;
	here_or_not(p);
	ms->e->fileout = -1;
	if (ms->e->out == true)
		check_fileout(p);
	ms->e->status = 0;
	ms->e->pid = NULL;
	ms->e->args = NULL;
	ms->e->paths = NULL;
	ms->e->path = NULL;
	ms->e->executable = NULL;
	ms->e->part = NULL;
	ms->e->cmd = NULL;
	ms->e->pid = malloc(sizeof(pid_t) * ms->e->cmd_count);
	if (!ms->e->pid)
		error(ms, NULL, 1);
	ms->e->pip = NULL;
	init_pipes(p);
}
*/
