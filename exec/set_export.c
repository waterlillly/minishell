/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_export.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbaumeis <lbaumeis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/03 11:59:53 by lbaumeis          #+#    #+#             */
/*   Updated: 2024/10/14 19:48:07 by lbaumeis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	update_export(t_pipex *p, char *tok, char *token)
{
	int		x;
	char	*temp;
	char	*temp1;

	x = 0;
	temp = NULL;
	temp1 = NULL;
	temp = ft_strjoin("declare -x ", tok);
	if (!temp)
		return (1);
	x = find_str_part(p->xport, temp);
	if (x == -1)
		return (free(temp), temp = NULL, 1);
	temp1 = ft_strjoin_free_both(ft_strdup("="),
		add_quotes(ft_substr(token, ft_strsrc(token, '=') + 1,
		ft_strlen(token) - (ft_strsrc(token, '=') + 1))));
	if (!temp1)
		return (free(temp), temp = NULL, 1);
	if (p->xport[x])
		free(p->xport[x]);
	p->xport[x] = NULL;
	p->xport[x] = ft_strjoin_free_both(temp, temp1);
	if (!p->xport[x])
		return (1);
	return (0);
}

static bool	check_edge_case(char **token)
{
	int	i;
	
	i = 0;
	if (ft_strcmp_bool(token[0], "export") && token[1])
	{
		while (token[1][i] && token[1][i] == '=')
			i++;
		if (token[1][i] && ft_isalpha(token[1][i]))
			return (true);
		return (false);
	}
	return (false);
}

int	set_export(t_pipex *p, char **token)
{
	char	*temp;
	char	*s;
	int		x;
	int		i;

	x = 0;
	i = 1;
	s = NULL;
	if (!p || !token || !token[1])
		return (1);
	if (ft_strcmp_bool(token[0], "export") && (ft_strcmp_bool(token[1], "=")))
		return (ft_putendl_fd("export: `=': not a valid identifier", 2), p->status = 1);
	else if (!check_edge_case(token))
	{
		s = ft_strjoin(ft_strjoin("export: ", token[1]), ": not a valid identifier");
		ft_putendl_fd(s, 2);
		return (p->status = 1);
	}
	while (token[i])
	{
		temp = strcpy_until(token[i]);
		if (!temp)
			return (1);
		if (valid_env(p, temp))
		{
			if (ft_strchr(token[i], '='))
			{
				x = find_str_part(p->menv, temp);
				if (x < 0)
					return (free(temp), temp = NULL, x);
				free(p->menv[x]);
				p->menv[x] = ft_strdup(token[i]);
				if (!p->menv[x])
					return (free(temp), temp = NULL, 1);
			}
			x = update_export(p, temp, token[i]);
		}
		else
			x = add_to_export(p, token[i]);
		i++;
	}
	return (free(temp), temp = NULL, x);
}

int	update(t_pipex *p, char *set, char *tok)
{
	char	*temp;
	int		x;

	temp = NULL;
	x = 0;
	if (!p || !set || !tok)
		return (0);
	x = find_str_part(p->menv, set);
	if (x < 0)
		return (1);
	temp = ft_strjoin(set, "=");
	if (!temp)
		return (1);
	if(p->menv && p->menv[x])
		free(p->menv[x]);
	p->menv[x] = NULL;
	p->menv[x] = ft_strjoin_free_one(temp, tok);
	if (!p->menv[x])
		return (1);
	x = update_export(p, set, tok);
	return (x);
}

int	update_both(t_pipex *p)
{
	int		x;

	x = 0;
	if(p->oldpwd)
		free(p->oldpwd);
	p->oldpwd = NULL;
	p->oldpwd = get_env(p, "PWD");
	x = update(p, "OLDPWD", p->oldpwd);
	if (x != 0)
		return (x);
	x = update(p, "PWD", p->pwd);
	return (x);
}
