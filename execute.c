/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbaumeis <lbaumeis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/15 16:27:28 by lbaumeis          #+#    #+#             */
/*   Updated: 2024/09/08 22:32:57 by lbaumeis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	redirect(t_pipex *p, int c, t_minishell_p *pars)
{
	check_fileout(p, pars);
	if (p->fileout != -1)
	{
		if (dup2(p->fileout, STDOUT_FILENO) == -1)
			return (perror("dup2 fileout"), 1);
		if (p->fileout != -1 && p->fileout != STDOUT_FILENO)
			close(p->fileout);
	}
	else if (p->cmd_count > 1 && c < p->cmd_count - 1)
	{
		if (c != 0 && p->pip[c][0] != -1 && p->pip[c][0] != STDIN_FILENO)
			close(p->pip[c][0]);
		if (dup2(p->pip[c][1], STDOUT_FILENO) == -1)
			return (perror("dup2 redir output"), 1);
		if (p->pip[c][1] != -1 && p->pip[c][1] != STDOUT_FILENO)
			close(p->pip[c][1]);
	}
	// else if (p->cmd_count == 1)
	// {
	// 	if (dup2(STDIN_FILENO, p->copy_stdin) == -1)
	// 		return (perror("dup2 single in"), 2);
	// }
	check_filein(p, pars);
	if (p->filein != -1)
	{
		if (dup2(p->filein, STDIN_FILENO) == -1)
			return (perror("dup2 filein"), 1);
		if (p->filein != -1 && p->filein != STDIN_FILENO)
			close(p->filein);
	}
	else if (p->cmd_count > 1 && c == 0)
	{
		if (p->pip[c][1] != -1 && p->pip[c][1] != STDOUT_FILENO)
			close(p->pip[c][1]);
		if (dup2(p->pip[c][0], STDIN_FILENO) == -1)
			return (perror("dup2 c=0 redir input"), 1);
		if (p->pip[c][0] != -1 && p->pip[c][0] != STDIN_FILENO)
			close(p->pip[c][0]);
	}
	else if (p->cmd_count > 1 && c > 0 && c < p->cmd_count)
	{
		if (p->pip[c - 1][1] != -1 && p->pip[c - 1][1] != STDOUT_FILENO)
			close(p->pip[c - 1][1]);
		if (dup2(p->pip[c - 1][0], STDIN_FILENO) == -1)
			return (perror("dup2 c - 1 redir input"), 1);
		if (p->pip[c - 1][0] != -1 && p->pip[c - 1][0] != STDIN_FILENO)
			close(p->pip[c - 1][0]);
	}
	// else if (p->cmd_count == 1)
	// {
	// 	if (dup2(STDOUT_FILENO, p->copy_stdout) == -1)
	// 		return (perror("dup2 single out"), 2);
	// }
	return (0);
}

int	execute(t_pipex *p, int c, t_minishell_p *pars)
{
	if (!p)
		return (1);
	if (redirect(p, c, pars) != 0)
		return (close_all(p), 1);
	//closing(p);
	return (exec_cmd(p, pars));
}
