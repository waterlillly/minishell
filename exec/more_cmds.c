/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   more_cmds.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbaumeis <lbaumeis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 18:09:17 by lbaumeis          #+#    #+#             */
/*   Updated: 2024/10/11 18:00:20 by lbaumeis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

bool	is_buildin(char *s)
{
	if ((ft_strcmp_bool(s, "unset")) || (ft_strcmp_bool(s, "env"))
		|| (ft_strcmp_bool(s, "export")) || (ft_strcmp_bool(s, "cd"))
		|| (ft_strcmp_bool(s, "echo")) || (ft_strcmp_bool(s, "pwd")))
		return (true);
	return (false);
}

int	do_this(t_pipex *p, t_minishell_p *pars)
{
	if (!p || !pars || !pars->ps)
		return (1);
	if (ft_strcmp_bool(pars->ps[0], "unset"))
		p->status = unset(p, pars->ps);
	else if (ft_strcmp_bool(pars->ps[0], "env") && p->menv)
		ft_print_array(p->menv);
	else if (ft_strcmp_bool(pars->ps[0], "export")
		&& pars->ps[1] == NULL && p->xport)
		ft_print_array(p->xport);
	else if (ft_strcmp_bool(pars->ps[0], "export")
		&& pars->ps[1] != NULL && p->xport)
		p->status = set_export(p, pars->ps);
	else if (ft_strcmp_bool(pars->ps[0], "cd"))
		p->status = cd(p, pars->ps);
	else if (ft_strcmp_bool(pars->ps[0], "echo"))
		p->status = echo(pars->ps);
	else if (ft_strcmp_bool(pars->ps[0], "pwd")) {
		ft_putendl_fd(p->pwd, 1);
		p->status = 0;
	}
	return (p->status);
}
