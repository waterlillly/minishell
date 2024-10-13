/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbaumeis <lbaumeis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/05 14:07:29 by lbaumeis          #+#    #+#             */
/*   Updated: 2024/10/13 21:30:20 by lbaumeis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_p_rest(t_pipex *p)
{
	if (p->home)
	{
		free(p->home);
		p->home = NULL;
	}
	if (p->pwd)
	{
		free(p->pwd);
		p->pwd = NULL;
	}
	if (p->oldpwd)
	{
		free(p->oldpwd);
		p->oldpwd = NULL;
	}
	// if (p->mpath)
	// {
	// 	free(p->mpath);
	// 	p->mpath = NULL;
	// }
	// if (p->cmd)
	// {
	// 	free(p->cmd);
	// 	p->cmd = NULL;
	// }
}

void	free_everything(t_pipex *p, t_minishell_p *pars, t_raw_in *input)
{
	if (input)
	{
		free_raw(input);
		input = NULL;
	}
	if (pars)
	{
		free_parse(pars);
		pars = NULL;
	}
	if (p)
		err_free(p);
}

void	free_parse(t_minishell_p *in)
{
	t_minishell_l	*tmp_l;
	t_minishell_p	*tmp_p;

	in = ft_lstfirst_parse(in);
	while (in)
	{
		tmp_p = in->next;
		while (in->redirect)
		{
			tmp_l = in->redirect->next;
			free(in->redirect);
			in->redirect = tmp_l;
		}
		if (in->str)
			free(in->str);
		ft_free_2d(in->ps);
		free(in);
		in = tmp_p;
	}
}

void	err_free(t_pipex *p)
{
	close_all(p);
	if (p->pid)
	{
		free(p->pid);
		p->pid = NULL;
	}
	if (p->here)
	{
		free(p->here);
		p->here = NULL;
	}
}
