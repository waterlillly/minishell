/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbaumeis <lbaumeis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 16:21:59 by lbaumeis          #+#    #+#             */
/*   Updated: 2024/09/18 14:52:55 by lbaumeis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exit_shell(t_pipex *p, t_minishell_p *pars, t_raw_in *input, char *str)
{
	close_all(p);
	if (p->pip)
	{
		free(p->pip);
		p->pip = 0;
	}
	if (p->paths)
		ft_free_2d(p->paths);//ft_free_2d(p->paths);
	if (p->xport)
		ft_free_2d(p->xport);//ft_free_2d(p->xport);
	if (p->menv)
		free(p->menv);
	free_p_rest(p);
	free_everything(p, pars, input);
	if (str)
		perror(str);
}

int	error(char *str, int code)
{
	perror(str);
	return (code);
}

void	free_p_rest(t_pipex *p)
{
	if (p->home)
	{
		free(p->home);
		p->home = NULL;
	}
	if (p->pwd)
	{
		free(p->pwd);
		p->pwd = NULL;
	}
	if (p->oldpwd)
	{
		free(p->oldpwd);
		p->oldpwd = NULL;
	}
	if (p->mpath)
	{
		free(p->mpath);
		p->mpath = NULL;
	}
	if (p->cmd)
	{
		free(p->cmd);
		p->cmd = NULL;
	}
}

void	free_everything(t_pipex *p, t_minishell_p *pars, t_raw_in *input)
{
	if (input)
	{
		free_raw(input);
		input = NULL;
	}
	if (pars)
	{
		free_parse(pars);
		pars = NULL;
	}
	if (p)
		err_free(p);
}

bool	check_exit(t_pipex *p, int *c, t_minishell_p **pars)
{
	char	*str;
	int		x;

	str = NULL;
	x = *c;
	if ((*pars) && (*pars)->str && ft_strcmp_bool((*pars)->str[0], "exit"))
	{
		if (!(*pars)->str[1] && !(*pars)->next)
			return (ft_putendl_fd("exit", 2), false);
		while ((*pars) && (*pars)->str && ft_strcmp_bool((*pars)->str[0], "exit"))
		{
			if ((*pars)->str[1] && ft_strcmp_bool(ft_itoa_long(ft_atoi_long((*pars)->str[1])), (*pars)->str[1]))
			{
				(p->status = ft_atoi_long((*pars)->str[1]), ft_putendl_fd("exit", 2));
				if (*c == x && !(*pars)->next)
					return (false);
				else if (*c > x && !(*pars)->next)
					return (true);
			}
			else if ((*pars)->str[1] && !(*pars)->str[2])
			{
				str = ft_strjoin_free_one(ft_strjoin_free_both(ft_strjoin((*pars)->str[0], ": "),
					ft_strjoin((*pars)->str[1], ": ")), "numeric argument required\n");
				p->status = 2;
				(ft_putendl_fd("exit", 2), ft_putstr_fd(str, 2), free(str), str = NULL);
				if (!(*pars)->next)
					return (true);
			}
			else if ((*pars)->str[1] && (*pars)->str[2])
			{
				str = ft_strjoin_free_one(ft_strjoin((*pars)->str[0], ": "), "too many arguments\n");
				p->status = 1;
				(ft_putendl_fd("exit", 2), ft_putstr_fd(str, 2), free(str), str = NULL);
				if (!(*pars)->next)
					return (true);
			}
			(*c)++;
			(*pars) = (*pars)->next;
		}
		if (*c > x && (*pars)->str && !ft_strcmp_bool((*pars)->str[0], "exit"))
			return (true);
	}
	return (true);
}
