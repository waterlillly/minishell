/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pre_exec.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbaumeis <lbaumeis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 14:42:56 by lbaumeis          #+#    #+#             */
/*   Updated: 2024/09/14 19:49:48 by lbaumeis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_access(t_pipex *p, char **cmd, t_minishell_p *pars)
{
	char	**temp;
	int		i;
	int		j;
	
	i = -1;
	j = 1;
	temp = NULL;
	temp = ft_split(pars->str[0], ' ');
	if (!temp)
		return (1);
	if (valid_cmd(temp, p))
	{
		cmd = ft_calloc(ft_arrlen(pars->str) + ft_arrlen(temp), sizeof(char *));
		if (!cmd)
			return (0);
		while (temp[++i])
			cmd[i] = ft_strdup(temp[i]);
		while (pars->str[j])
			cmd[i++] = ft_strdup(pars->str[j++]);
		pars->str = update_free_arr(pars->str, cmd);
		return (ft_free_double(temp), 0);
	}
	return (perror(pars->str[0]), 127);
}

int	check(t_pipex *p, t_minishell_p *pars)
{
	char	**cmd;
	

	cmd = NULL;
	if (p->cmd_count > 500)
	{
		ft_putendl_fd("too many commands", 2);
		return (p->status = 1);
	}
	else if (p && pars->str)
	{
		cmd = check_cmd(p, pars);
		if (!cmd)
			return (p->status = 1);
		pars->str = update_free_arr(pars->str, cmd);
		if (valid_cmd(pars->str, p) || is_buildin(pars->str[0]))
			return (p->status = 0);
		if (access(pars->str[0], X_OK) != 0)
			return (p->status = check_access(p, cmd, pars));
		else
			return (perror(pars->str[0]), p->status = 1);
	}
	return (p->status = 1);
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

char	*loop_cmd_check(t_pipex *p, t_minishell_p *pars, int x)
{
	char	**s;
	char	*temp;

	s = NULL;
	temp = NULL;
	if (!s_out_q(pars->str[x]) && !only_dollars(pars->str[x])
		&& !ft_strcmp_bool(pars->str[x], "$?"))
	{
		s = echo_split(rm_q(pars->str[x]), '$');
		if (!s)
			temp = xpand(p, pars->str, x);
		else
		{
			temp = split_and_xpand(p, s);
			if (!temp)
				return (ft_free_double(s), NULL);
		}
	}
	else
		temp = ft_strdup(pars->str[x]);
	return (temp);
}

char	**check_cmd(t_pipex *p, t_minishell_p *pars)
{
	char	**cmd;
	int		x;

	x = 0;
	cmd = NULL;
	cmd = ft_calloc(ft_arrlen(pars->str) + 1, sizeof(char *));
	if (!cmd)
		return (NULL);
	while (pars && pars->str[x])
	{
		if (only_dollars(pars->str[x]) || ft_strcmp_bool(pars->str[x], "$?")
			|| (x > 0 && ft_strcmp_bool(pars->str[x - 1], "echo")))
			cmd[x] = ft_strdup(pars->str[x]);
		else
			cmd[x] = loop_cmd_check(p, pars, x);
		if (!cmd[x])
			return (ft_free_2d(cmd), NULL);
		x++;
	}
	return (cmd);
}
