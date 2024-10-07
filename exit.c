/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbaumeis <lbaumeis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 16:21:59 by lbaumeis          #+#    #+#             */
/*   Updated: 2024/10/05 14:07:22 by lbaumeis         ###   ########.fr       */
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
		ft_free_2d(p->xport);//ft_free_double(p->xport);
	if (p->menv)
		ft_free_2d(p->menv);
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



bool	check_exit(t_pipex *p, int *c, t_minishell_p **pars)
{
	char	*str;
	int		x;

	str = NULL;
	x = *c;
	if ((*pars) && (*pars)->ps && ft_strcmp_bool((*pars)->ps[0], "exit"))
	{
		if (!(*pars)->ps[1] && !(*pars)->next)
			return (ft_putendl_fd("exit", 2), false);
		while ((*pars) && (*pars)->ps && ft_strcmp_bool((*pars)->ps[0], "exit"))
		{
			if ((*pars)->ps[1] && ft_strcmp_bool(ft_itoa_long(ft_atoi_long((*pars)->ps[1])), (*pars)->ps[1]) && !(*pars)->ps[2])
			{
				(p->status = ft_atoi_long((*pars)->ps[1]), ft_putendl_fd("exit", 2));
				if (*c == x && !(*pars)->next)
					return (false);
				else if (*c > x && !(*pars)->next)
					return (true);
			}
			else if ((*pars)->ps[1] && !(*pars)->ps[2])
			{
				str = ft_strjoin_free_one(ft_strjoin_free_both(ft_strjoin((*pars)->ps[0], ": "),
					ft_strjoin((*pars)->ps[1], ": ")), "numeric argument required\n");
				p->status = 2;
				(ft_putendl_fd("exit", 2), ft_putstr_fd(str, 2), free(str), str = NULL);
				if (!(*pars)->next)
					return (true);
			}
			else if ((*pars)->ps[1] && (*pars)->ps[2])
			{
				str = ft_strjoin_free_one(ft_strjoin((*pars)->ps[0], ": "), "too many arguments\n");
				p->status = 1;
				(ft_putendl_fd("exit", 2), ft_putstr_fd(str, 2), free(str), str = NULL);
				if (!(*pars)->next)
					return (true);
			}
			(*c)++;
			(*pars) = (*pars)->next;
		}
		if (*c > x && (*pars)->ps && !ft_strcmp_bool((*pars)->ps[0], "exit"))
			return (true);
	}
	return (true);
}
