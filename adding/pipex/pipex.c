/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbaumeis <lbaumeis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 06:41:43 by lbaumeis          #+#    #+#             */
/*   Updated: 2024/08/17 17:26:46 by lbaumeis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*is_exec(t_pipex *p)
{
	int	i;

	i = 0;
	if (access(p->cmd, X_OK) == 0)
		return (p->cmd);
	while (p->paths[i])
	{
		p->executable = ft_strjoin(p->paths[i], "/");
		if (!p->executable)
			return (NULL);//error(p, "strjoin failed", p->status);
		p->part = ft_strjoin(p->executable, p->cmd);
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
	return (NULL);
}

int	exec_cmd(t_pipex *p, t_minishell_p *pars)
{
	if (!p || !pars || !pars->str)
		return (error("idk", 1));
	if (pars->str[0][0] == '$'
		&& valid_env(p, ft_substr(pars->str[0], 1, ft_strlen(pars->str[0]) - 1)))
		p->cmd = xpand(p, pars->str, 0);
	else
		p->cmd = pars->str[0];
	if (is_buildin(p->cmd))
	{
		do_this(p, pars);
		return (0);
	}
	else
	{
		p->path = is_exec(p);
		if (!p->path)
			return (error("command not found", 127));
		execve(p->path, pars->str, p->menv);
		return (-1);//error(p, "execve failed", p->status);
	}
	return (-1);
}
