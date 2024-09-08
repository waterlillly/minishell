/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mehras <mehras@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/15 16:27:28 by lbaumeis          #+#    #+#             */
/*   Updated: 2024/09/08 14:06:50 by mehras           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	redir_input(t_pipex *p, int c, t_minishell_p *pars)
{
	check_filein(p, pars);
	if (p->filein != -1)
	{
		if (dup2(p->filein, STDIN_FILENO) == -1)
			return (perror("dup2 filein"), 1);
		if (close(p->filein) != 0)
			return (1);
	}
	else if (p && p->pip && c > 0 && p->cmd_count > 1 && p->pip[c - 1])
	{
		if (close(p->pip[c - 1][1]) != 0)
			return (1);
		if (dup2(p->pip[c - 1][0], STDIN_FILENO) == -1)
			return (perror("dup2 c - 1 redir input"), 1);
		if (close(p->pip[c - 1][0]) != 0)
			return (1);
	}
	else if (p && p->pip && c == 0 && p->cmd_count >= 1 && p->pip[c])
	{
		if (close(p->pip[c][1]) != 0)
			return (1);
		if (dup2(p->pip[c][0], STDIN_FILENO) == -1)
			return (perror("dup2 c = 0 redir input"), 1);
		if (close(p->pip[c][0]) != 0)
			return (1);
	}
	return (0);
}

int	redir_output(t_pipex *p, int c, t_minishell_p *pars)
{
	check_fileout(p, pars);
	if (p->fileout != -1)
	{
		if (dup2(p->fileout, STDOUT_FILENO) == -1)
			return (perror("dup2 fileout"), 1);
		if (close(p->fileout) != 0)
			return (1);
	}
	else if (p && p->pip && c < p->cmd_count - 1 && p->pip[c])
	{
		if (close(p->pip[c][1]) != 0)
			return (1);
		if (dup2(p->pip[c][1], STDOUT_FILENO) == -1)
			return (perror("dup2 redir output"), 1);
		if (close(p->pip[c][0]) != 0)
			return (1);
	}
	return (0);
}

int	execute(t_pipex *p, int c, t_minishell_p *pars)
{
	int	x;

	x = 0;
	if (!p)
		return (1);
	x = redir_input(p, c, pars);
	if (x == 0)
		return (x);
	x = redir_output(p, c, pars);
	if (x == 0)
		return (x);
	ft_putendl_fd("a child came here", 1);
	closing(p);//close_all(p);
	return (exec_cmd(p, pars));
}
