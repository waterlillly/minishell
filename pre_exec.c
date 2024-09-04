/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pre_exec.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbaumeis <lbaumeis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 14:42:56 by lbaumeis          #+#    #+#             */
/*   Updated: 2024/09/04 15:58:54 by lbaumeis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	check_access(t_pipex *p, t_minishell_p *pars, char **cmd)
{
	char	**temp;
	int		i;
	int		j;
	
	i = -1;
	j = 1;
	temp = NULL;
	temp = ft_split(pars->str[0], ' ');
	if (!temp)
		return ;
	if (valid_cmd(temp, p))
	{
		cmd = ft_calloc(ft_arrlen(pars->str) + ft_arrlen(temp), sizeof(char *));
		if (!cmd)
			return ;
		while (temp[++i])
			cmd[i] = ft_strdup(temp[i]);
		while (pars->str[j])
			cmd[i++] = ft_strdup(pars->str[j++]);
		ft_free_double(pars->str);
		pars->str = cmd;
		return (ft_free_double(temp));
	}
	return (perror(pars->str[0]));
}

void	check(t_pipex *p, t_minishell_p *pars)
{
	char	**cmd;

	cmd = NULL;
	if (p->cmd_count > 500)
	{
		ft_putendl_fd("too many commands", 2);
		p->status = 1;
		return ;
	}
	else if (p && pars && pars->str)
	{
		cmd = check_cmd(p, pars);
		if (!cmd)
			return ;
		ft_free_double(pars->str);
		pars->str = cmd;
		if (valid_cmd(pars->str, p) || is_buildin(pars->str[0]))
			return ;
		else if (access(pars->str[0], X_OK) != 0)
			return (check_access(p, pars, cmd));
		return (perror(pars->str[0]));
	}
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
		p->part = ft_strjoin(p->executable, str[0]);
		free(p->executable);
		p->executable = NULL;
		if (!p->part)
			return (false);
		if (access(p->part, X_OK) == 0)
			return (true);
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
	if (!s_out_q(pars->str[x]) && !only_dollars(pars->str[x]))
	{
		s = echo_split(remove_quotes(pars->str[x]), '$');
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
		if (only_dollars(pars->str[x]) || ft_strcmp_bool(pars->str[x], "$?"))
			cmd[x] = ft_strdup(pars->str[x]);
		else
		{
			cmd[x] = ft_strdup(loop_cmd_check(p, pars, x));
			if (!cmd[x])
				return (NULL);
		}
		x++;
	}
	return (cmd);
}
