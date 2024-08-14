/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   more_cmds.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbaumeis <lbaumeis@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 18:09:17 by lbaumeis          #+#    #+#             */
/*   Updated: 2024/08/14 20:54:59 by lbaumeis         ###   ########.fr       */
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

void	do_this(t_pipex *p)
{
	int		x;

	if (ft_strcmp_bool(p->args[0], "unset"))
		unset(p, p->args);
	else if (ft_strcmp_bool(p->args[0], "env"))
		ft_print_array(p->menv);
	else if (ft_strcmp_bool(p->args[0], "export") && p->args[1] == NULL)
		ft_print_array(p->xport);
	else if (ft_strcmp_bool(p->args[0], "export") && p->args[1] != NULL)
		set_export(p, p->args);
	else if (ft_strcmp_bool(p->args[0], "cd"))
		cd(p, p->args);
	else if (ft_strcmp_bool(p->args[0], "echo"))
		echo(p, p->args);
	else if (ft_strcmp_bool(p->args[0], "exit"))
	{
		if (p->args[1] == NULL)
		{
			err_free(p);
			exit(0);
		}
		else
		{
			x = ft_atoi(p->args[1]);
			err_free(p);
			exit(x);
		}
	}
}
