/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbaumeis <lbaumeis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 14:55:29 by lbaumeis          #+#    #+#             */
/*   Updated: 2024/08/23 15:11:51 by lbaumeis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	here_or_not(t_pipex *p, t_minishell_p *pars)
{
	if (pars && pars->redirect && pars->redirect->token == HEREDOC)
		p->here = pars->redirect->str;
	else if (pars && !pars->infile)
		p->cwd = get_env(p, "PWD");
}
