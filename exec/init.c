/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbaumeis <lbaumeis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 06:41:58 by lbaumeis          #+#    #+#             */
/*   Updated: 2024/10/09 13:33:30 by lbaumeis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	init_pipes(t_pipex *p)
{
	int i;

	i = 0;
	if (!p)
		return ;
	p->pip = NULL;
	if (p->cmd_count > 1)
	{
		p->pip = (int **)ft_calloc(p->cmd_count, sizeof(int *));
		if (!p->pip)
			return ;
	}
	while (p->cmd_count > 1 && i < p->cmd_count)
	{
		p->pip[i] = (int *)ft_calloc(2, sizeof(int));
		if (!p->pip[i])
			return ;
		if (pipe(p->pip[i]) == -1)
			return (perror("pipe"));
		i++;
	}
}

void	init_p(t_pipex *p, t_minishell_p *pars)
{
	t_minishell_p	*tmp;

	tmp = pars;
	p->cmd_count = 0;
	while (tmp)
	{
		p->cmd_count++;
		tmp = tmp->next;
	}
	p->filein = -1;
	p->fileout = -1;
	p->here = NULL;
	if (pars && pars->redirect && pars->redirect->token == HEREDOC)
		p->here = ft_strdup(pars->redirect->str);
	p->path = NULL;
	p->executable = NULL;
	p->part = NULL;
	p->cmd = NULL;
	p->pid = (pid_t *)ft_calloc(p->cmd_count, sizeof(pid_t));
	if (!p->pid)
		return ;
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
	p->paths = ft_split(p->mpath, ':');
	if (!p->paths)
		return (p->status = 1, err_free(p), 1);
	return (0);
}
