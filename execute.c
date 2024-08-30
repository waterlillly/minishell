/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbaumeis <lbaumeis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/15 16:27:28 by lbaumeis          #+#    #+#             */
/*   Updated: 2024/08/30 18:08:32 by lbaumeis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	redir_input(t_pipex *p, int *c, t_minishell_p *pars)
{
	check_filein(p, pars);
	if (p->filein != -1)
	{
		if (dup2(p->filein, STDIN_FILENO) == -1)
			return (perror("dup2"), 1);
		close(p->filein);
	}
	else if (*c == p->cmd_count - 1)
	{
		if (dup2(p->temp_in, STDIN_FILENO) == -1)
			return (perror("dup2"), 1);
		close(p->temp_in);
	}
	else if (*c > 0)
	{
		if (dup2(p->pip[*c - 1][0], STDIN_FILENO) == -1)
			return (perror("dup2"), 1);
		close(p->pip[*c - 1][0]);
	}
	return (0);
}

int	redir_output(t_pipex *p, int *c, t_minishell_p *pars)
{
	check_fileout(p, pars);
	if (p->fileout != -1)
	{
		if (dup2(p->fileout, STDOUT_FILENO) == -1)
			return (perror("dup2"), 1);
		close(p->fileout);
	}
	else if (*c < p->cmd_count - 1)
	{
		if (p->temp_in != -1)
		{
			if (dup2(p->temp_in, STDOUT_FILENO) == -1)
				return (perror("dup2"), 1);
			close(p->temp_in);
		}
		else
		{
			if (dup2(p->pip[*c][1], STDOUT_FILENO) == -1)
				return (perror("dup2"), 1);
			close(p->pip[*c][1]);
		}
	}
	return (0);
}

int	execute(t_pipex *p, int *c, t_minishell_p *pars)
{
	int	x;

	x = 0;
	if (!p)
		return (1);
	x = redir_input(p, c, pars);
	if (x != 0)
		return (x);
	x = redir_output(p, c, pars);
	if (x != 0)
		return (x);
	close_all(p);
	return (exec_cmd(p, pars));
}
