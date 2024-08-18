/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   backup.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbaumeis <lbaumeis@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/18 15:30:52 by lbaumeis          #+#    #+#             */
/*   Updated: 2024/08/18 17:02:48 by lbaumeis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	backup_env(t_pipex *p, char *temp)
{
	p->menv = NULL;
	p->menv = malloc(sizeof(char *) * 3);
	if (!p->menv)
		return (1);
	p->menv[0] = ft_strjoin("PWD=", temp);
	if (!p->menv[0])
		return (1);
	p->menv[1] = ft_strdup("SHLVL=1");
	if (!p->menv[1])
		return (1);
	p->menv[2] = NULL;
	if (!p->menv)
		return (1);
	return (0);
}

int	backup_xport(t_pipex *p, char *temp)
{
	p->xport = NULL;
	p->xport = malloc(sizeof(char *) * 4);
	if (!p->xport)
		return (1);
	p->xport[0] = create_add_export("OLDPWD");
	if (!p->xport[0])
		return (1);
	p->xport[1] = create_add_export(ft_strjoin("PWD=", temp));
	if (!p->xport[1])
		return (1);
	p->xport[2] = create_add_export("SHLVL=1");
	if (!p->xport[2])
		return (1);
	p->xport[3] = NULL;
	p->xport = resort_arr(p->xport);
	if (!p->xport)
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
	if (!temp || access(temp, R_OK) != 0)
		return (err_free(p), 1);
	if (backup_env(p, temp) || backup_xport(p, temp))
		return (free(temp), temp = NULL, 1);
	return (free(temp), temp = NULL, 0);
}
