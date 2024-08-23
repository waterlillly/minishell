/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbaumeis <lbaumeis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 06:41:58 by lbaumeis          #+#    #+#             */
/*   Updated: 2024/08/23 15:33:10 by lbaumeis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	check_filein(t_pipex *p, t_minishell_p *pars)
{
	if (pars && pars->redirect && pars->redirect->input
		&& pars->redirect->token == SMALLER)
	{
		p->filein = -1;
		p->filein = open(pars->redirect->input, O_RDONLY, 0644);
		if (p->filein == -1 || access(pars->redirect->input, R_OK) == -1)
			return ;
	}
}

void	check_fileout(t_pipex *p, t_minishell_p *pars)
{
	char	*file;

	file = NULL;
	if (pars && pars->redirect && pars->redirect->input)
		file = pars->redirect->input;
	else
		return ;
	if (file && pars->redirect->token == BIGGER)
	{
		p->fileout = -1;
		p->fileout = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (p->fileout == -1 || access(file, W_OK) == -1)
			return ;
	}
	else if (file && pars->redirect->token == BIGGERBIGGER)
	{
		p->fileout = -1;
		p->fileout = open(file, O_WRONLY | O_CREAT | O_APPEND, 0644);
		if (p->fileout == -1 || access(file, W_OK) == -1)
			return ;
	}
}

void init_pipes(t_pipex *p)
{
	int i;

	i = 0;
	if (!p)
		return ;
	p->pip = NULL;
	if (p->cmd_count > 1)
	{
		p->pip = (int **)ft_calloc(sizeof(int *), p->cmd_count);
		if (!p->pip)
			return ;
	}
	while (p->cmd_count > 1 && i < (p->cmd_count - 1))
	{
		p->pip[i] = NULL;
		p->pip[i] = (int *)ft_calloc(2, sizeof(int));
		if (!p->pip[i])
			return ;
		if (pipe(p->pip[i]) == -1)
			return ;
		i++;
	}
}

void	init_p(t_pipex *p, t_minishell_p *pars)
{
	t_minishell_p	*tmp;

	tmp = NULL;
	tmp = pars;
	if (!tmp)
		return ;
	p->copy_stdin = dup(STDIN_FILENO);
	p->copy_stdout = dup(STDOUT_FILENO);
	p->cmd_count = 0;
	while (tmp)
	{
		p->cmd_count++;
		tmp = tmp->next;
	}
	p->filein = -1;
	p->fileout = -1;
	p->here = NULL;
	here_or_not(p, pars);
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

int	first_init(t_pipex *p, char **envp)
{
	int	x;

	x = 0;
	p->status = 0;
	x = buildins_init(p, envp);
	if (x != 0)
		return (p->status = x, x);
	p->cwd = NULL;
	p->copy_stdin = -1;
	p->copy_stdout = -1;
	p->paths = ft_split(p->mpath, ':');
	if (!p->paths)
		return (p->status = 1, 1);
	return (x);
}
