/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbaumeis <lbaumeis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 06:41:43 by lbaumeis          #+#    #+#             */
/*   Updated: 2024/10/13 21:46:38 by lbaumeis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static bool check_permissions(t_pipex* p)
{
	DIR	*dir;

	dir = opendir(p->cmd);	
	if (dir)
	{
		ft_putstr_fd(p->cmd, 2), ft_putendl_fd(": Is a directory", 2), p->status = 126;
		return (false);
	}
	else if (access(p->cmd, F_OK))
	{
		ft_putstr_fd(p->cmd, 2), ft_putendl_fd(": No such file or directory", 2), p->status = 127;
		return (false);
	}
	else if (access(p->cmd, R_OK))
	{
		ft_putstr_fd(p->cmd, 2), ft_putendl_fd(": Permission denied", 2), p->status = 126;
		return (false);
	}
	return (true);
}

char	*is_exec(t_pipex *p)
{
	int	i;

	i = 0;
	if (!p || !p->cmd)
		return (NULL);
	if (ft_strchr(p->cmd, '/'))
	{
		if (!check_permissions(p))
			return (NULL);
	}
	if (access(p->cmd, X_OK) == 0)
		return (p->cmd);
	if (!p->paths)
	{
		(ft_putstr_fd(p->cmd, 2), ft_putendl_fd(": No such file or directory", 2));
		p->status = 127;
		return (NULL);
	}
	while (p->paths[i])
	{
		p->executable = ft_strjoin(p->paths[i], "/");
		if (!p->executable)
			return (NULL);
		p->part = ft_strjoin_free_one(p->executable, p->cmd);
		if (!p->part)
			return (NULL);
		else if (access(p->part, X_OK) == 0)
			return (p->part);
		else
		{
			free(p->part);
			p->part = NULL;
			i++;
		}
	}
	(ft_putstr_fd(p->cmd, 2), ft_putendl_fd(": command not found", 2));
	p->status = 127;
	return (NULL);
}

int	do_heredoc(t_pipex *p, t_minishell_p *pars)
{
	char	**new;
	int		x;

	new = NULL;
	x = -1;
	if (!p || !pars || !pars->redirect || !pars->redirect->str)
		return (0);
	if (check_s_q(pars->redirect->input) || check_d_q(pars->redirect->input))
		return (ft_putstr_fd(rm_out_q(pars->redirect->str), 1), 0);
	new = ft_split(pars->redirect->str, '\n');
	if (!new)
		return (1);
	while (new[++x])
	{
		do_echo(new, x, 0);
		if (new[x + 1] != NULL)
			ft_putstr_fd("\n", 1);
	}
	ft_putchar_fd('\n', 1);
	ft_free_double(new);
	return (0);
}

int	exec_cmd(t_pipex *p, t_minishell_p *pars)
{
	if (!p || !pars || !pars->ps)
		return (p->status = 1);
	if (pars->redirect && pars->redirect->token == HEREDOC)
	{
		p->status = do_heredoc(p, pars);
		return (1);
	}
	p->cmd = pars->ps[0];
	if (is_buildin(p->cmd))
	{
		p->status = do_this(p, pars);
		return (1);
	}
	p->path = is_exec(p);
	if (!p->path)
		return (p->status);
	p->mode = INTER;
	return (p->status = execve(p->path, pars->ps, p->menv));
}
