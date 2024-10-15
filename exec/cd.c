/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbaumeis <lbaumeis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/28 11:38:34 by lbaumeis          #+#    #+#             */
/*   Updated: 2024/10/14 18:15:41 by lbaumeis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void ft_chdir(char *target_dir, t_pipex *p)
{
	char	*current_pwd;

	current_pwd = getcwd(NULL, 0);
	if (chdir(target_dir))
	{
		free(current_pwd);
		ft_putstr_fd("cd: ", 2);
		perror(target_dir);
		p->status = 1;
		return ;
	}
	update(p, "OLDPWD", current_pwd);
	free(p->oldpwd);
	p->oldpwd = get_env(p, "OLDPWD");
	free(current_pwd);
	current_pwd = getcwd(NULL, 0);
	update(p, "PWD", current_pwd);
	free(p->pwd);
	p->pwd = get_env(p, "PWD");
	free(current_pwd);
}

int	cd(t_pipex *p, char **token)
{
	char	*home;
	
	if (!p || !token)
		return (1);
	if (ft_arrlen(token) > 2)
		return (ft_putendl_fd("cd: too many arguments", 2), p->status = 1);
	if (!token[1])
	{
		home = get_env(p, "HOME");//TODO: RETURN NULL FOR GETENV
		if(home && *home == '\n')
			return (ft_putendl_fd("cd: HOME not set", 2), p->status = 1);
		return (ft_chdir(home, p), free(home), p->status);
	}
	if (ft_strcmp_bool(token[0], "cd") && ft_strcmp_bool(token[1], "-"))
	{
		ft_chdir(get_env(p, "OLDPWD"), p);
		return (p->status);
	}
	ft_chdir(token[1], p);
	return (p->status);
}