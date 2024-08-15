/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbaumeis <lbaumeis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/15 16:27:28 by lbaumeis          #+#    #+#             */
/*   Updated: 2024/08/15 17:22:05 by lbaumeis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	redir_input(t_pipex *p, int *c)
{
	if (p->here == true)
	{
		p->filein = open("hd", O_RDONLY);
		if (p->filein == -1 || access("hd", R_OK) == -1)
			return ;//error(p, "hd", p->status);
	}
	check_filein(p);
	if (p->filein > -1)
	{
		if (dup2(p->filein, STDIN_FILENO) == -1)
		return ;//error(p, "dup2 failed", p->status);
	}
	else if (*c > 0)
	{
		if (dup2(p->pip[*c - 1][0], STDIN_FILENO) == -1)
		return ;//error(p, "dup2 failed", p->status);
	}
}

void	redir_output(t_pipex *p, int *c)
{
	check_fileout(p);
	if (p->fileout > -1)
	{
		if (dup2(p->fileout, STDOUT_FILENO) == -1)
			return ;//error(p, "dup2 failed", p->status);
	}
	else if (*c == p->cmd_count - 1)
	{
		if (dup2(STDOUT_FILENO, p->copy_stdout) == -1)
			return ;//error(p, "dup2 failed", p->status);
	}
	else if (*c < p->cmd_count - 1)
	{
		if (dup2(p->pip[*c][1], STDOUT_FILENO) == -1)
		return ;//error(p, "dup2 failed", p->status);
	}
}

void	execute(t_pipex *p, int *c)
{
	redir_input(p, c);
	redir_output(p, c);
	close_all(p);
	//close_pipes(p);
	if (exec_cmd(p) < 0)
		return ;//error(p, "exec_cmd failed", p->status);
}
