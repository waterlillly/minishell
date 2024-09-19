/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbaumeis <lbaumeis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 06:41:43 by lbaumeis          #+#    #+#             */
/*   Updated: 2024/09/19 16:43:20 by lbaumeis         ###   ########.fr       */
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
			return (NULL);
		p->part = ft_strjoin_free_one(p->executable, p->cmd);
		// free(p->executable);
		// p->executable = NULL;
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
	return (NULL);
}

int	do_heredoc(t_pipex *p, t_minishell_p *pars)
{
	char	**new;
	int		x;

	new = NULL;
	x = -1;
	if (!p || !pars || !pars->redirect || !pars->redirect->str || !pars->str)
		return (0);
	if (check_s_q(pars->redirect->input) || check_d_q(pars->redirect->input))
		return (ft_putstr_fd(rm_out_q(pars->redirect->str), 1), 0);
	new = ft_split(pars->redirect->str, '\n');
	if (!new)
		return (1);
	while (new[++x])
	{
		do_echo(p, new, x);
		if (new[x + 1] != NULL)
			ft_putstr_fd("\n", 1);
	}
	ft_putchar_fd('\n', 1);
	ft_free_double(new);
	return (0);
}

int	exec_cmd(t_pipex *p, t_minishell_p *pars)
{
	char	*temp;

	temp = NULL;
	if (!p || !pars || !pars->str)
		return (p->status = 1);
	if (pars->redirect && pars->redirect->token == HEREDOC)
	{
		p->status = do_heredoc(p, pars);
		return (1);
	}
	temp = ft_substr(pars->str[0], 1, ft_strlen(pars->str[0]) - 1);
	if (!temp)
		return (1);
	if (pars->str[0][0] == '$' && valid_env(p, temp))
		p->cmd = xpand(p, pars->str, 0);
	else
		p->cmd = pars->str[0];
	free(temp);
	temp = NULL;
	if (is_buildin(p->cmd))
	{
		p->status = do_this(p, pars);
		return (1);
	}
	p->path = is_exec(p);
	return (p->status = execve(p->path, pars->str, p->menv));
}
