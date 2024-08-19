/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbaumeis <lbaumeis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 14:55:29 by lbaumeis          #+#    #+#             */
/*   Updated: 2024/08/19 17:56:47 by lbaumeis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	get_cur_cwd(t_pipex *p)
{
	p->cwd = get_env(p, "PWD");
	if (!p->cwd)
		return ;//error(p, "get_env failed", p->status);
	if (access(p->cwd, F_OK) == -1)
	{
		free(p->cwd);
		p->cwd = NULL;
		return ;//error(p, "no access", p->status);
	}
}

void	here_or_not(t_pipex *p, t_minishell_p *pars)
{
	if (pars && pars->redirect && pars->redirect->token == HEREDOC)
		p->here = pars->redirect->str;
	else
	{
		if (pars && !pars->infile)
			get_cur_cwd(p);
	}
}
