/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbaumeis <lbaumeis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 06:41:43 by lbaumeis          #+#    #+#             */
/*   Updated: 2024/08/19 19:03:22 by lbaumeis         ###   ########.fr       */
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

void	do_heredoc(t_pipex *p, t_minishell_p *pars)
{
	char	**new;
	int		x;

	new = NULL;
	x = -1;
	if (pars->redirect->str[0] == '\''
		&& pars->redirect->str[ft_strlen(pars->redirect->str) - 1] == '\'')
	{
		ft_putendl_fd(ft_substr(pars->redirect->str, 1, ft_strlen(pars->redirect->str) - 1), 1);
		return ;
	}
	new = ft_split(pars->redirect->str, ' ');
	if (!new)
		return ;
	while (new[++x])
	{
		if (do_echo(p, new, x) == 0)
		{
			if (new[x + 1] != NULL)
				ft_putstr_fd(" ", 1);
		}
		x++;
	}
	free(new);
	new = NULL;
}

int	exec_cmd(t_pipex *p, t_minishell_p *pars)
{
	if (!p || !pars || !pars->str || !pars->str[0])
		return (1);
	if (p && pars && pars->redirect && pars->redirect->token == HEREDOC)
	{
		do_heredoc(p, pars);
		close_all(p);
		return (0);
	}
	if (pars->str[0][0] == '$'
		&& valid_env(p, ft_substr(pars->str[0], 1, ft_strlen(pars->str[0]) - 1)))
		p->cmd = xpand(p, pars->str, 0);
	else
		p->cmd = pars->str[0];
	if (is_buildin(p->cmd))
	{
		do_this(p, pars);
		close_all(p);
		return (0);
	}
	else
	{
		p->path = is_exec(p);
		if (!p->path)
			return (error(p->path, 0));
		close_all(p);
		return (execve(p->path, pars->str, p->menv));
	}
	close_all(p);
	return (0);
}
