/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbaumeis <lbaumeis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 06:41:58 by lbaumeis          #+#    #+#             */
/*   Updated: 2024/08/16 16:54:23 by lbaumeis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	check_filein(t_pipex *p, t_minishell_p *pars)
{
	if (pars->infile)
	{
		p->filein = -1;
		p->filein = open(pars->infile, O_RDONLY, 0644);
		if (p->filein == -1 || access(pars->infile, R_OK) == -1)
			return ;//error(p, p->todo[1], p->status);
	}
}

void	check_fileout(t_pipex *p, t_minishell_p *pars)
{
	if (pars->outfile && pars->redirect->token == BIGGER)
	{
		p->fileout = -1;
		p->fileout = open(pars->outfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (p->fileout == -1 || access(pars->outfile, W_OK) == -1)
			return ;//error(p, pars->outfile, p->status);
	}
	else if (pars->outfile && pars->redirect->token == BIGGERBIGGER)
	{
		p->fileout = -1;
		p->fileout = open(pars->outfile, O_WRONLY | O_CREAT | O_APPEND, 0644);
		if (p->fileout == -1 || access(pars->outfile, W_OK) == -1)
			return ;//error(p, pars->outfile, p->status);
	}
}

void init_pipes(t_pipex *p)
{
	int i;

	i = 0;
	if (p->cmd_count > 1)
	{
		p->pip = NULL;
		p->pip = malloc(p->cmd_count * sizeof(int *));
		if (!p->pip)
			return ;//error(p, "malloc failed", p->status);
		while (i < p->cmd_count && p->cmd_count > 1)
		{
			p->pip[i] = NULL;
			p->pip[i] = malloc(sizeof(int) * 2);
			if (!p->pip[i])
				return ;//error(p, "malloc failed", p->status);
			if (pipe(p->pip[i]) == -1)
				return ;//error(p, "pipe failed", p->status);
			i++;
		}
	}
}

void	init_p(t_pipex *p, t_minishell_p *pars)
{
	t_minishell_p	*tmp;

	tmp = pars;
	if (!tmp)
		error("syntax error", 1);
	p->cmd_count = 0;
	while (tmp)
	{
		p->cmd_count++;
		tmp = tmp->next;
	}
	p->cwd = NULL;
	p->delimiter = NULL;
	p->filein = -1;
	p->fileout = -1;
	here_or_not(p, pars);
	p->args = NULL;
	p->paths = ft_split(p->mpath, ':');
	if (!p->paths)
		return ;//error(p, "ft_split failed", p->status);
	p->path = NULL;
	p->executable = NULL;
	p->part = NULL;
	p->cmd = NULL;
	p->pid = NULL;
	p->pid = malloc(sizeof(pid_t) * p->cmd_count);
	if (!p->pid)
		return ;//error(p, "malloc failed", p->status);
	init_pipes(p);
}

void	first_init(t_pipex *p, char **envp)
{
	p->status = 0;
	buildins_init(p, envp);
	p->copy_stdout = dup(STDOUT_FILENO);
	if (p->copy_stdout == -1)
		return ;//error(p, "dup failed", p->status);
	p->cwd = NULL;
}
