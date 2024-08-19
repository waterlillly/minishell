/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   more_cmds.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbaumeis <lbaumeis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 18:09:17 by lbaumeis          #+#    #+#             */
/*   Updated: 2024/08/19 17:15:04 by lbaumeis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	is_buildin(char *s)
{
	if ((ft_strcmp_bool(s, "unset")) || (ft_strcmp_bool(s, "env"))
		|| (ft_strcmp_bool(s, "export")) || (ft_strcmp_bool(s, "cd"))
		|| (ft_strcmp_bool(s, "echo")) || (ft_strcmp_bool(s, "exit")))
		return (true);
	return (false);
}

void	do_this(t_pipex *p, t_minishell_p *pars)//add returns
{
	int		x;

	if (ft_strcmp_bool(pars->str[0], "unset"))
		unset(p, pars->str);
	else if (ft_strcmp_bool(pars->str[0], "env"))
		ft_print_array(p->menv);
	else if (ft_strcmp_bool(pars->str[0], "export") && pars->str[1] == NULL)
		ft_print_array(p->xport);
	else if (ft_strcmp_bool(pars->str[0], "export") && pars->str[1] != NULL)
		set_export(p, pars->str);
	else if (ft_strcmp_bool(pars->str[0], "cd"))
		cd(p, pars->str);
	else if (ft_strcmp_bool(pars->str[0], "echo"))
		echo(p, pars->str);
	else if (ft_strcmp_bool(pars->str[0], "exit"))
	{
		if (pars->str[1] == NULL)
		{
			err_free(p);
			exit(0);
		}
		else
		{
			x = ft_atoi(pars->str[1]);
			err_free(p);
			exit(x);
		}
	}
}
