/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgardesh <mgardesh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 06:41:43 by lbaumeis          #+#    #+#             */
/*   Updated: 2024/08/21 17:47:21 by mgardesh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*is_exec(t_pipex *p)
{
	int	i;

	i = 0;
	if (access(p->cmd, X_OK) == 0)
		return (p->cmd);
	while (p->paths[i])
	{
		p->executable = ft_strjoin(p->paths[i], "/");
		if (!p->executable)
			return (NULL);//error(p, "strjoin failed", p->status);
		p->part = ft_strjoin(p->executable, p->cmd);
		free(p->executable);
		p->executable = NULL;
		if (!p->part)
			return (NULL);//error(p, "strjoin failed", p->status);
		if (access(p->part, X_OK) == 0)
			return (p->part);
		free(p->part);
		p->part = NULL;
		i++;
	}
	return (NULL);
}

int	do_heredoc(t_pipex *p, t_minishell_p *pars)
{
	char	**new;
	int		x;
	int		y;

	new = NULL;
	x = -1;
	y = 0;
	if (!p || !pars || !pars->redirect || !pars->redirect->str)
		return (0);
	if (s_out_q(pars->redirect->str))
		return (ft_putendl_fd(rm_out_q(pars->redirect->str), 1), 0);
	new = ft_split(pars->redirect->str, ' ');
	if (!new)
		return (1);
	while (new[++x])
	{
		y = do_echo(p, new, x);
		if (y != 0)
			return (ft_free_double(new), y);
		if (new[x + 1] != NULL)
			ft_putstr_fd(" ", 1);
	}
	ft_free_double(new);
	return (0);
}

int	exec_cmd(t_pipex *p, int *c, t_minishell_p *pars)
{
	int	x;

	x = 0;
	(void)c;
	if (!p || !pars || !pars->str)
		return (1);
	if (pars->redirect && pars->redirect->token == HEREDOC)
	{
		x = do_heredoc(p, pars);
		return (close_all(p), x);
	}
	if (pars->str[0][0] == '$' && valid_env(p, ft_substr(pars->str[0], 1,
		ft_strlen(pars->str[0]) - 1)))
		p->cmd = xpand(p, pars->str, 0);
	else
		p->cmd = pars->str[0];
	if (is_buildin(p->cmd))
	{
		x = do_this(p, pars);
		return (close_all(p), x);
	}
	p->path = is_exec(p);
	if (!p->path)
		return (error(p->path, 0));
	close_all(p);
	return (execve(p->path, pars->str, p->menv));
}
