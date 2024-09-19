/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbaumeis <lbaumeis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/28 11:38:34 by lbaumeis          #+#    #+#             */
/*   Updated: 2024/09/19 12:34:29 by lbaumeis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	cd_home(t_pipex *p)
{
	if (p && p->home && is_access(p->home))
	{
		reset_old_pwd(p, p->home);
		return (chdir(p->home));
	}
	return (1);
}

int	fill_path(t_pipex *p, char **token)
{
	int	x;

	if (!p || !token || !token[1])
		return (1);
	if (ft_strcmp_bool(token[1], "-"))
		return (go_back(p, 1));
	else if (ft_strcmp_bool(token[1], ".."))
	{
		x = go_up_oldpwd(p);
		if (x == 0)
		{
			if (ft_strcmp_bool(p->pwd, "/"))
				return (update(p, "OLDPWD", "/"));
			else
				return (go_back(p, 0));
		}
		return (x);
	}
	else if (token[1][0] == '/' && token[1][1] != '\0'
		&& token[1][1] != '/')
		return (go_full_path(p, token));
	else if (token[1][0] == '/')
		return (go_slash(p, token));
	else
		return (add_to_path(p, token[1]));
}

int	cd(t_pipex *p, char **token)
{
	char	*err;

	err = NULL;
	if (p && token && ft_strcmp_bool(token[0], "cd"))
	{
		if (token[1] == NULL)
			p->status = cd_home(p);
		else if (token[1][0] == '.' && token[1][1] == '\0')
			return (0);
		else if (token[1] != NULL)
			p->status = fill_path(p, token);
	}
	if (find_str_part(p->menv, "PWD") == -1)
	{
		update_unset(p, "PWD");
		add_to_export(p, ft_strjoin("PWD=", p->pwd));
		return (update(p, "PWD", p->pwd), update(p, "OLDPWD", p->oldpwd));
	}
	if (p->status != 0)
	{
		err = ft_strjoin("cd: ", token[1]);
		return (perror(err), free(err), err = NULL, 0);
	}
	return (update_both(p));
}
