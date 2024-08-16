/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbaumeis <lbaumeis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 06:41:43 by lbaumeis          #+#    #+#             */
/*   Updated: 2024/08/16 17:05:59 by lbaumeis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*is_exec(t_pipex *p)
{
	int	i;

	i = 0;
	if (access(p->cmd, X_OK) == 0)
		return (p->cmd);
	//ft_print_array(p->paths);
	while (p->paths[i])
	{
		p->executable = ft_strjoin(p->paths[i], "/");
		if (!p->executable)
			return (NULL);//error(p, "strjoin failed", p->status);
		p->part = ft_strjoin(p->executable, p->cmd);
		//printf("executable: %s\n", p->part);
		free(p->executable);
		p->executable = NULL;
		if (!p->part)
			return (NULL);//error(p, "strjoin failed", p->status);
		if (access(p->part, X_OK) == 0)
			return (p->part);
		free(p->part);
		p->part = NULL;
		i++;
	}
	error("command not found", 127);
	return (NULL);
}

int	exec_cmd(t_pipex *p, t_minishell_p *pars)
{
	p->args = pars->str;
	if (p->args[0][0] == '$'
		&& valid_env(p, ft_substr(p->args[0], 1, ft_strlen(p->args[0]) - 1)))
		p->cmd = xpand(p, p->args, 0);
	else
		p->cmd = p->args[0];
	if (is_buildin(p->cmd))
	{
		do_this(p);
		return (p->status);
	}
	else
	{
		p->path = is_exec(p);
		execve(p->path, p->args, p->menv);
		return (-1);//error(p, "execve failed", p->status);
	}
	return (p->status);
}
