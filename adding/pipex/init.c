/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbaumeis <lbaumeis@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 06:41:58 by lbaumeis          #+#    #+#             */
/*   Updated: 2024/08/14 15:38:49 by lbaumeis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	check_filein(t_pipex *p)
{
	if (!p->delimiter && !p->cwd)
	{
		p->filein = open(p->av[1], O_RDONLY, 0644);
		if (p->filein == -1 || access(p->av[1], R_OK) == -1)
			return ;//error(p, p->av[1], p->status);
	}
}

void	check_fileout(t_pipex *p)
{
	int	x;

	x = p->x + p->cmd_count;
	if (p->appd == false)
	{
		p->fileout = open(p->av[x], O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (p->fileout == -1 || access(p->av[x], W_OK) == -1)
			return ;//error(p, p->av[x], p->status);
	}
	else
	{
		p->fileout = open(p->av[x], O_WRONLY | O_CREAT | O_APPEND, 0644);
		if (p->fileout == -1 || access(p->av[x], W_OK) == -1)
			return ;//error(p, p->av[x], p->status);
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

void	init_p(t_pipex *p, t_minishell_p *parser)
{
	p->parser = parser;
	p->filein = -1;
	if (parser->std_out == true)
		p->out = false;
	else
		p->out = true;
	p->cwd = NULL;
	p->av = parser->str;
	p->in = false;
	p->appd = false;
	here_or_not(p);
	p->fileout = -1;
	if (p->out == true)
		check_fileout(p);
	p->args = NULL;
	p->paths = NULL;
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