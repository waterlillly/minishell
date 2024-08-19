/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbaumeis <lbaumeis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/15 16:27:28 by lbaumeis          #+#    #+#             */
/*   Updated: 2024/08/19 13:27:32 by lbaumeis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	redir_input(t_pipex *p, int *c, t_minishell_p *pars)
{
	if (p->here == true)
	{
		p->filein = open("hd", O_RDONLY);
		if (p->filein == -1 || access("hd", R_OK) == -1)
			return (error("hd", p->status));
	}
	if (pars->infile)
		check_filein(p, pars);
	if (p->filein > -1)
	{
		if (dup2(p->filein, STDIN_FILENO) == -1)
		return (error("dup2 failed", p->status));
	}
	else if (*c > 0)
	{
		if (dup2(p->pip[*c - 1][0], STDIN_FILENO) == -1)
		return (error("dup2 failed", p->status));
	}
	return (0);
}

int	redir_output(t_pipex *p, int *c, t_minishell_p *pars)
{
	if (pars->outfile)
		check_fileout(p, pars);
	if (p->fileout != -1)
	{
		if (dup2(p->fileout, STDOUT_FILENO) == -1)
			return (error("dup2 failed", p->status));
	}
	else if (*c < p->cmd_count - 1)
	{
		if (dup2(p->pip[*c][1], STDOUT_FILENO) == -1)
		return (error("dup2 failed", p->status));
	}
	else if (*c == p->cmd_count - 1)
	{
		if (dup2(STDOUT_FILENO, p->copy_stdout) == -1)
			return (error("dup2 failed", p->status));
		//if (dup2(STDIN_FILENO, p->copy_stdin) == -1)
		//	return (error("dup2 failed", p->status));
	}
	return (0);
}

int	execute(t_pipex *p, int *c, t_minishell_p *pars)
{
	int	x;

	x = 0;
	//if (p->cmd_count == 1)
	//	return (close_all(p), single_exec(p, pars));
	//else
	//{
	x = redir_input(p, c, pars);
	if (x != 0)
		return (x);
	x = redir_output(p, c, pars);
	if (x != 0)
		return (x);
	close_all(p);
	return (exec_cmd(p, pars));
	//}
	//return (1);
}
