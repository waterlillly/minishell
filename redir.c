/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbaumeis <lbaumeis@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 16:50:42 by lbaumeis          #+#    #+#             */
/*   Updated: 2024/09/17 20:09:11 by lbaumeis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	check_filein(t_pipex *p, t_minishell_p *pars)
{
	int				f;
	t_minishell_l	*redir;

	redir = pars->redirect;
	if (p && pars && redir)
	{
		while (redir)
		{
			f = -1;
			if (redir->token == SMALLER)
			{
				f = open(redir->input, O_RDONLY, 0644);
				if (f == -1 || access(redir->input, R_OK) == -1)
					return (perror(redir->input));
			}
			if (f != -1)
			{
				if (!redir->next)
					p->filein = f;
				close(f);
			}
			redir = redir->next;
		}
	}
}

void	check_fileout(t_pipex *p, t_minishell_p *pars)
{
	int				f;
	t_minishell_l	*redir;

	redir = pars->redirect;
	if (p && pars && redir)
	{
		while (redir)
		{
			f = -1;
			if (redir->token == BIGGER)
			{
				f = open(redir->input, O_WRONLY | O_CREAT | O_TRUNC, 0644);
				if (f == -1 || access(redir->input, W_OK) == -1)
					return (perror("file"));
			}
			else if (redir->token == BIGGERBIGGER)
			{
				f = open(redir->input, O_RDWR | O_CREAT | O_APPEND, 0644);
				if (f == -1 || access(redir->input, W_OK) == -1)
					return (perror("file"));
			}
			if (f != -1)
			{
				if (!redir->next)
					p->fileout = f;
				else
					close(f);
			}
			redir = redir->next;
		}
	}
}
