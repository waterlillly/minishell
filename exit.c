/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbaumeis <lbaumeis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 16:21:59 by lbaumeis          #+#    #+#             */
/*   Updated: 2024/09/01 14:57:48 by lbaumeis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exit_shell(t_pipex *p, t_minishell_p *pars, t_raw_in *input, char *str)
{
	//restore_fds(p);
	//close_all(p);
	if (p->paths)
		ft_free_2d(p->paths);
	if (p->xport)
		ft_free_2d(p->xport);
	if (p->menv)
		ft_free_double(p->menv);
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
	if (p)
		err_free(p);
	if (pars)
		free_parse(pars);
	if (input)
		free_raw(input);
}
