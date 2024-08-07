/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   more_cmds.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbaumeis <lbaumeis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 18:09:17 by lbaumeis          #+#    #+#             */
/*   Updated: 2024/08/07 22:10:24 by lbaumeis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

bool	is_buildin(char *s)
{
	if ((ft_strcmp(s, "unset")) || (ft_strcmp(s, "env"))
		|| (ft_strcmp(s, "export")) || (ft_strcmp(s, "cd"))
		|| (ft_strcmp(s, "echo")) || (ft_strcmp(s, "exit")))
		return (true);
	return (false);
}

void	do_this(t_pipex *p)
{
	if (ft_strcmp(p->cmd, "unset"))
		unset(p, p->av);
	else if (ft_strcmp(p->cmd, "env"))
		ft_print_array(p->menv);
	else if (ft_strcmp(p->cmd, "export") && p->args[1] == NULL)
		ft_print_array(p->xport);
	else if (ft_strcmp(p->cmd, "export") && p->args[1] != NULL)
		set_export(p, p->av);
	else if (ft_strcmp(p->cmd, "cd"))
		cd(p, p->av);
	else if (ft_strcmp(p->cmd, "echo"))
		echo(p, p->av);
	else if (ft_strcmp(p->cmd, "exit"))
		error(p, NULL, 0);
	else if (ft_strcmp(p->cmd, "exit"))
	{
		err_free(p);
		if (p->args[1] == NULL)
			exit(0);
		else
			exit(ft_atoi(p->args[1]));
	}
}
