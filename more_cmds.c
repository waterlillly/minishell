/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   more_cmds.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbaumeis <lbaumeis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 18:09:17 by lbaumeis          #+#    #+#             */
/*   Updated: 2024/09/04 19:14:24 by lbaumeis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	is_buildin(char *s)
{
	if ((ft_strcmp_bool(s, "unset")) || (ft_strcmp_bool(s, "env"))
		|| (ft_strcmp_bool(s, "export")) || (ft_strcmp_bool(s, "cd"))
		|| (ft_strcmp_bool(s, "echo")))// || (ft_strcmp_bool(s, "expr")))
		return (true);
	return (false);
}

int	do_this(t_pipex *p, t_minishell_p *pars)
{
	if (!p || !pars || !pars->str)
		return (0);
	if (ft_strcmp_bool(pars->str[0], "unset"))
		p->status = unset(p, pars->str);
	else if (ft_strcmp_bool(pars->str[0], "env") && p->menv)
		ft_print_array(p->menv);
	else if (ft_strcmp_bool(pars->str[0], "export") && pars->str[1] == NULL && p->xport)
		ft_print_array(p->xport);
	else if (ft_strcmp_bool(pars->str[0], "export") && pars->str[1] != NULL && p->xport)
		p->status = set_export(p, pars->str);
	else if (ft_strcmp_bool(pars->str[0], "cd"))
		p->status = cd(p, pars->str);
	else if (ft_strcmp_bool(pars->str[0], "echo"))
		p->status = echo(p, pars->str);
	//else if (ft_strcmp_bool(pars->str[0], "expr") && pars->str[1] != NULL)
	//	p->status = expr(p, pars->str);
	return (0);
}

