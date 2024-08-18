/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbaumeis <lbaumeis@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/28 11:38:34 by lbaumeis          #+#    #+#             */
/*   Updated: 2024/08/18 17:24:04 by lbaumeis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	cd_home(t_pipex *p)
{
	if (!p->home)
		p->home = get_env(p, "HOME");
	if (is_access(p->home))
	{
		reset_old_pwd(p, p->home);
		return (chdir(p->home));
	}
	return (1);//error(p, p->home, p->status)
}

int	fill_path(t_pipex *p, char **token)
{
	if (token[1][0] == '-' && token[1][1] == '\0')
	{
		if (ft_strcmp_bool(p->pwd, p->oldpwd))
		{
			if (go_up_oldpwd(p))
				return (1);
		}
		return (go_back(p, 1));
	}
	else if (token[1][0] == '.' && token[1][1] == '.'
		&& token[1][2] == '\0')
	{
		if (go_up_oldpwd(p))
			return (1);
		return (go_back(p, 0));
	}
	else if (token[1][0] == '/' && token[1][1] != '\0'
		&& token[1][1] != '/')
		return (go_full_path(p, token));
	else if (token[1][0] == '/')
		return (go_slash(p, token));
	else
		return (add_to_path(p, token[1]));
	return (1);//error(p, token[1], p->status)
}

int	cd(t_pipex *p, char **token)
{
	//if (token[x + 1] == NULL || ft_strcmp_bool(token[x + 1], "#")
	//	|| (token[x + 1][0] == '-' && token[x + 1][1] == '-'
	//	&& token[x + 1][2] == '\0'))
	if (p && token && ft_strcmp_bool(token[0], "cd"))
	{
		if (token[1] == NULL)
			return (cd_home(p));
		else if (token[1][0] == '.' && token[1][1] == '\0')
			return (0);
		else if (token[1] != NULL)
			return (fill_path(p, token));
	}
	perror("cd");
	return (1);
}
