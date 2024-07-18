/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   processes.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbaumeis <lbaumeis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 06:41:51 by lbaumeis          #+#    #+#             */
/*   Updated: 2024/07/18 20:25:07 by lbaumeis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	first(t_pipex *p, char **envp)
{
	if (dup2(p->filein, STDIN_FILENO) == -1)
		err_free(p, 1);
	if (dup2(p->pip[p->c][1], STDOUT_FILENO) == -1)
		err_free(p, 1);
	close_pipes(p);
	exec_cmd(p->av, p->x, p, envp);
	err_free(p, 1);
}

void	middle(t_pipex *p, char **envp)
{
	if (dup2(p->pip[p->c - 1][0], STDIN_FILENO) == -1)
		err_free(p, 1);
	if (dup2(p->pip[p->c][1], STDOUT_FILENO) == -1)
		err_free(p, 1);
	close_pipes(p);
	exec_cmd(p->av, p->x, p, envp);
	err_free(p, 1);
}

void	last(t_pipex *p, char **envp)
{
	if (dup2(p->pip[p->c - 1][0], STDIN_FILENO) == -1)
		err_free(p, 1);
	if (dup2(p->fileout, STDOUT_FILENO) == -1)
		err_free(p, 1);
	close_pipes(p);
	exec_cmd(p->av, p->x, p, envp);
	err_free(p, 1);
}

void	do_child(t_pipex *p, char ** envp)
{
	if (p->c == 0)
		first(p, envp);
	else if (p->c == p->cmd_count - 1)
		last(p, envp);
	else
		middle(p, envp);
}
