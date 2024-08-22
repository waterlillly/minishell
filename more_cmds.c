/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   more_cmds.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbaumeis <lbaumeis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 18:09:17 by lbaumeis          #+#    #+#             */
/*   Updated: 2024/08/22 19:41:38 by lbaumeis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	is_buildin(char *s)
{
	if ((ft_strcmp_bool(s, "unset")) || (ft_strcmp_bool(s, "env"))
		|| (ft_strcmp_bool(s, "export")) || (ft_strcmp_bool(s, "cd"))
		|| (ft_strcmp_bool(s, "echo")))
		return (true);
	return (false);
}

int	do_this(t_pipex *p, t_minishell_p *pars)
{
	if (ft_strcmp_bool(pars->str[0], "unset"))
		return (unset(p, pars->str));
	else if (ft_strcmp_bool(pars->str[0], "env"))
		return (ft_print_array(p->menv), 0);
	else if (ft_strcmp_bool(pars->str[0], "export") && pars->str[1] == NULL)
		return (ft_print_array(p->xport), 0);
	else if (ft_strcmp_bool(pars->str[0], "export") && pars->str[1] != NULL)
		return (set_export(p, pars->str));
	else if (ft_strcmp_bool(pars->str[0], "cd"))
		return (cd(p, pars->str));
	else if (ft_strcmp_bool(pars->str[0], "echo"))
		return (echo(p, pars->str));
	return (1);
}

