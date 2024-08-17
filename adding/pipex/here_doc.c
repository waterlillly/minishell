/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbaumeis <lbaumeis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 14:55:29 by lbaumeis          #+#    #+#             */
/*   Updated: 2024/08/17 15:27:36 by lbaumeis         ###   ########.fr       */
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

void	first_heredoc(t_pipex *p)
{
	char	*line;
	
	line = NULL;
	p->filein = -1;
	p->filein = open("hd", O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (p->filein == -1 || access("hd", R_OK) == -1 || access("hd", W_OK) == -1)
		return ;//error(p, "hd", p->status);
	line = readline("> ");
	while (line && !ft_strcmp_bool(line, p->delimiter))
	{
		ft_putstr_fd(line, p->filein);
		ft_putchar_fd('\n', p->filein);
		free(line);
		line = NULL;
		line = readline("> ");
	}
	close_all(p);
}

void	here_or_not(t_pipex *p, t_minishell_p *pars)
{
	if (pars && pars->redirect && pars->redirect->token == HEREDOC)
	{
		p->delimiter = pars->str[1];
		p->here = true;
		first_heredoc(p);
	}
	else
	{
		p->delimiter = NULL;
		p->here = false;
		if (pars && !pars->infile)
			get_cur_cwd(p);
	}
}
