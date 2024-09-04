/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbaumeis <lbaumeis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 16:21:59 by lbaumeis          #+#    #+#             */
/*   Updated: 2024/09/04 15:06:01 by lbaumeis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exit_shell(t_pipex *p, t_minishell_p *pars, t_raw_in *input, char *str)
{
	//restore_fds(p);
	close_all(p);
	if (p->paths)
		ft_free_double(p->paths);//ft_free_2d(p->paths);
	if (p->xport)
		ft_free_double(p->xport);//ft_free_2d(p->xport);
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
	{
		free_parse(pars);
		pars = NULL;
	}
	if (input)
	{
		free_raw(input);
		input = NULL;
	}
}

void	check_exit(t_pipex *p, t_minishell_p *pars)
{
	char	*str;
	char	*temp;

	str = NULL;
	temp = NULL;
	temp = ft_itoa_long(ft_atoi_long(pars->str[1]));
	if (ft_strcmp_bool(temp, pars->str[1]))
	{
		p->status = ft_atoi_long(pars->str[1]);
		return (free(temp), temp = NULL, (void)NULL);
	}
	str = ft_strjoin_free_both(ft_strjoin(pars->str[0], ": "),
		ft_strjoin(pars->str[1], ": "));
	if (pars->str[2])
	{
		str = ft_strjoin_free_one(str, "too many arguments\n");
		p->status = 1;
	}
	else
	{
		str = ft_strjoin_free_one(str, "numeric argument required\n");
		p->status = 2;
	}
	ft_putstr_fd(str, 2);
	return (free(str), str = NULL, free(temp), temp = NULL, (void)NULL);
}
