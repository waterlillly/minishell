/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbaumeis <lbaumeis@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/04 18:54:32 by lbaumeis          #+#    #+#             */
/*   Updated: 2024/10/15 21:37:38 by lbaumeis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	update_unset(t_pipex *p, char *tok)
{
	int		x;
	int		y;
	char	**arr;

	x = 0;
	y = 0;
	if (!p || !tok || !p->menv)
		return (0);
	arr = NULL;
	arr = ft_calloc((ft_arrlen(p->menv) + 1), sizeof(char *));
	if (!arr)
		return (1);
	while (p->menv[x])
	{
		if (ft_strnstr_bool(p->menv[x], tok, 0, ft_strlen(tok)))
			x++;
		else
			arr[y++] = ft_strdup(p->menv[x++]);
	}
	p->menv = update_free_arr(p->menv, arr);
	if (!p->menv)
		return (1);
	return (update_unset_exp(p, tok));
}

int	update_unset_exp(t_pipex *p, char *tok)
{
	int		x;
	int		y;
	char	**arr;

	x = 0;
	y = 0;
	if (!p || !tok || !p->xport)
		return (0);
	arr = NULL;
	arr = ft_calloc((ft_arrlen(p->xport) + 1), sizeof(char *));
	if (!arr)
		return (1);
	while (p->xport[x])
	{
		if (ft_strnstr_bool(p->xport[x], tok, 11, ft_strlen(tok)))
			x++;
		else
			arr[y++] = ft_strdup(p->xport[x++]);
	}
	p->xport = update_free_arr(p->xport, arr);
	if (!p->xport)
		return (1);
	return (0);
}

int	unset(t_pipex *p, char **token)
{
	int		x;
	int		i;
	size_t	len;

	if (!p || !p->menv || !token)
		return (0);
	i = 0;
	while (token[i])
	{		
		x = 0;
		if (ft_strcmp_bool(token[i], "_"))
			continue ;
		len = ft_strlen(token[i]);
		while (p->menv[x])
		{
			if (ft_strnstr_bool(p->menv[x], token[i], 0, len)) {
				update_unset(p, token[i]);
				break ;
			}
			x++;
		}
		x = 0;
		while (p->xport[x])
		{
			if (ft_strnstr_bool(p->xport[x], token[i], 11, len)) {
				update_unset_exp(p, token[i]);
				break;
			}
			x++;
		}
		i++;
	}
	return (0);
}

void	check_unset(t_pipex *p)
{
	if (!p)
		return ;
	if (p->menv && p->xport && !valid_env(p, "PWD"))
	{
		if (p->pwd)
			add_to_export(p, ft_strjoin("PWD=", p->pwd));
	}
	if (p->menv && p->xport && !valid_env(p, "OLDPWD"))
	{
		if (p->oldpwd)
			add_to_export(p, ft_strjoin("OLDPWD=", p->oldpwd));
	}
}
