/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   backup.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbaumeis <lbaumeis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/18 15:30:52 by lbaumeis          #+#    #+#             */
/*   Updated: 2024/08/27 15:52:23 by lbaumeis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	backup_env(t_pipex *p, char *temp)
{
	char	*new;

	new = NULL;
	p->menv = ft_calloc(3, sizeof(char *));
	if (!p->menv)
		return (1);
	new = ft_strjoin("PWD=", temp);
	if (!new)
		return (1);
	p->menv[0] = ft_strdup(new);
	free(new);
	new = NULL;
	if (!p->menv[0])
		return (1);
	new = ft_strdup("SHLVL=1");
	if (!new)
		return (1);
	p->menv[1] = ft_strdup(new);
	free(new);
	new = NULL;
	if (!p->menv[1])
		return (1);
	return (0);
}

int	backup_xport(t_pipex *p, char *temp)
{
	char	*new;

	new = NULL;
	p->xport = ft_calloc(4, sizeof(char *));
	if (!p->xport)
		return (1);
	new = create_add_export("OLDPWD");
	if (!new)
		return (1);
	p->xport[0] = ft_strdup(new);
	free(new);
	new = NULL;
	if (!p->xport[0])
		return (1);
	new = create_add_export(ft_strjoin("PWD=", temp));
	if (!new)
		return (1);
	p->xport[1] = ft_strdup(new);
	free(new);
	new = NULL;
	if (!p->xport[1])
		return (1);
	new = create_add_export("SHLVL=1");
	if (!new)
		return (1);
	p->xport[2] = ft_strdup(new);
	free(new);
	new = NULL;
	if (!p->xport[2])
		return (1);
	return (0);
}

int	backup(t_pipex *p)
{
	char	*temp;
	
	temp = NULL;
	if (!p)
		return (1);
	temp = getcwd(temp, 0);
	if (!temp)
		return (1);
	else if (access(temp, R_OK) != 0)
		return (free(temp), temp = NULL, 1);
	if (backup_env(p, temp) || backup_xport(p, temp))
		return (free(temp), temp = NULL, 1);
	return (free(temp), temp = NULL, 0);
}
