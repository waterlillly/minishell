/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbaumeis <lbaumeis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/27 13:48:57 by lbaumeis          #+#    #+#             */
/*   Updated: 2024/08/17 14:46:09 by lbaumeis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	how_many(char **s, char *o)
{
	int	x;
	int	y;

	x = 0;
	y = 0;
	while (s[x])
	{
		if (ft_strcmp_bool(s[x], o))
			y++;
		x++;
	}
	return (y);
}

bool	is_access(char *dir)
{
	if ((access(dir, F_OK) == 0))
		return (true);
	return (false);
}

int	find_arg(char **s, char *a)
{
	int	x;

	x = 0;
	if (!s || !a)
		return (-1);
	while (s[x])
	{
		if (ft_strcmp_bool(s[x], a))
			return (x);
		x++;
	}
	return (-1);
}

int	buildins_init(t_pipex *p, char **envp)
{
	get_menv(p, envp);
	get_pwd(p);
	go_up_oldpwd(p);
	p->home = get_env(p, "HOME");
	if (!p->home)
		return (err_free(p), 1);//error(p, "get_env failed", p->status);
	p->mpath = get_env(p, "PATH");
	if (!p->home)
		return (err_free(p), 1);//error(p, "get_env failed", p->status);
	return (combine_export(p));
}

char	*remove_quotes(char *s)
{
	int		x;
	int		y;
	char	*temp;

	x = 0;
	y = 0;
	temp = NULL;
	if (!s || ft_strlen(s) < 2)
		return (NULL);
	temp = malloc(sizeof(char) * (ft_strlen(s) - 1));
	if (!temp)
		return (NULL);
	while (s[x])
	{
		if (s[x] == '\"' || s[x] == '\'')
			x++;
		else
		{
			temp[y] = s[x];
			y++;
			x++;
		}
	}
	temp[y] = '\0';
	return (temp);
}
