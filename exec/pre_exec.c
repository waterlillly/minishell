/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pre_exec.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbaumeis <lbaumeis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 14:42:56 by lbaumeis          #+#    #+#             */
/*   Updated: 2024/10/13 15:17:43 by lbaumeis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_access(t_pipex *p, t_minishell_p *pars)
{
	if (valid_cmd(pars->ps, p))
		return (0);
	//ft_putstr_fd(": ", 2); //TODO remove for submit
	ft_putstr_fd(pars->ps[0], 2);
	return (ft_putendl_fd(": command not found", 2), 127);
}

int	check(t_pipex *p, t_minishell_p *pars)
{
	if (p->cmd_count > 500)
	{
		ft_putendl_fd("too many commands", 2);
		return (p->status = 1);
	}
	else if (p && pars->ps)
	{
		if (valid_cmd(pars->ps, p) || is_buildin(pars->ps[0]))
			return (0);
		if (access(pars->ps[0], X_OK) != 0)
			return (p->status = check_access(p, pars));
		else
			return (perror(pars->ps[0]), p->status = 1);
	}
	return (1);
}

bool	valid_cmd(char **str, t_pipex *p)
{
	int	i;

	i = -1;
	if (!str)
		return (false);
	if (access(str[0], X_OK) == 0)
		return (true);
	while (p->paths[++i])
	{
		p->executable = ft_strjoin(p->paths[i], "/");
		if (!p->executable)
			return (false);
		p->part = ft_strjoin_free_one(p->executable, str[0]);
		if (!p->part)
			return (false);
		if (access(p->part, X_OK) == 0)
			return (free(p->part), p->part = NULL, true);
		free(p->part);
		p->part = NULL;
	}
	return (false);
}

char	**check_cmd(t_minishell_p *pars)
{
	char	**cmd;
	int		x;

	x = 0;
	cmd = NULL;
	cmd = ft_calloc(ft_arrlen(pars->ps) + 1, sizeof(char *));
	if (!cmd)
		return (NULL);
	while (pars && pars->ps[x])
	{
		cmd[x] = pars->ps[x];
		x++;
	}
	return (cmd);
}
