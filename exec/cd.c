/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbaumeis <lbaumeis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/28 11:38:34 by lbaumeis          #+#    #+#             */
/*   Updated: 2024/10/05 20:19:31 by lbaumeis         ###   ########.fr       */
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

int	go_back_minus(t_pipex *p, int print)
{
	char	*temp;
	int		x;

	temp = NULL;
	x = 0;
	if (!p)
		return (1);
	temp = get_env(p, "OLDPWD");
	if (!temp)
		return (1);
	if (is_access(temp))
	{
		reset_old_pwd(p, temp);
		if (print == 1)
			check_print(p->pwd);
		x = chdir(temp);
	}
	else
		x = 1;
	return (free(temp), temp = NULL, x);
}

int	fill_path(t_pipex *p, char **token)
{
	int	x;

	x = 0;
	if (!p || !token || !token[1])
		return (1);
	if (ft_strcmp_bool(token[1], "-"))
		return (go_back_minus(p, 1));
	else if (ft_strcmp_bool(token[1], ".."))
	{
		x = go_up_oldpwd(p);
		if (ft_strcmp_bool(p->pwd, "/"))
			return (update(p, "OLDPWD", "/"));
		if (x == 0)
			return (go_back(p, 0));
		return (0);
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
	char	*idk;
	char	**new;

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
	if (!get_env(p, "PWD"))
	{
		if (!p->pwd)
			p->pwd = get_env(p, "HOME");
		new = ft_calloc(3, sizeof(char *));
		if (!new)
			return (1);
		new[0] = "";
		new[1] = ft_strjoin("PWD=", p->pwd);
		set_export(p, new);
		ft_free_double(new);
		//update(p, "PWD", p->pwd);
	}
	if (p->status != 0)
	{
		idk = NULL;
		idk = get_env(p, "PWD");
		err = ft_strjoin_free_both(ft_strdup("cd: "), idk);
		return (perror(err), free(err), err = NULL, 0);
	}
	return (update(p, "OLDPWD", get_env(p, "PWD")), update(p, "PWD", p->pwd));
}
