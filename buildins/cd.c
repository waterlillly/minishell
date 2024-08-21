/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgardesh <mgardesh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/28 11:38:34 by lbaumeis          #+#    #+#             */
/*   Updated: 2024/08/21 17:48:50 by mgardesh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	cd_home(t_pipex *p)
{
	int	x;

	x = 0;
	if (p && p->home && is_access(p->home))
	{
		reset_old_pwd(p, p->home);
		x = chdir(p->home);
		//if (x == 0)
		//	x = update_both(p);
		return (x);
	}
	return (1);
}

int	fill_path(t_pipex *p, char **token)
{
	int	x;

	if (!p || !token || !token[1])
		return (1);
	if (token[1][0] == '-' && token[1][1] == '\0')
		x = go_back(p, 1);
	else if (token[1][0] == '.' && token[1][1] == '.'
		&& token[1][2] == '\0')
	{
		x = go_up_oldpwd(p);
		if (x == 0)
			x = go_back(p, 0);
	}
	else if (token[1][0] == '/' && token[1][1] != '\0'
		&& token[1][1] != '/')
		x = go_full_path(p, token);
	else if (token[1][0] == '/')
		x = go_slash(p, token);
	else
	{
		x = add_to_path(p, token[1]);
		if (x != 0)
			return (perror(token[1]), x);
	}
	return (x);
}

int	cd(t_pipex *p, char **token)
{
	int	x;

	x = 0;
	if (p && token && ft_strcmp_bool(token[0], "cd"))
	{
		if (token[1] == NULL)
			x = cd_home(p);
		else if (token[1][0] == '.' && token[1][1] == '\0')
			return (0);
		else if (token[1] != NULL)
			x = fill_path(p, token);
		else
			return (perror(token[1]), 1);
	}
	//if (x == 0)
	//	x = update_both(p);
	if (x != 0)
		return (perror("cd"), x);
	return (x);
}
