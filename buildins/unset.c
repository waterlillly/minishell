/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbaumeis <lbaumeis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/04 18:54:32 by lbaumeis          #+#    #+#             */
/*   Updated: 2024/08/20 16:32:00 by lbaumeis         ###   ########.fr       */
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
	arr = malloc(sizeof(char *) * (ft_arrlen(p->menv)));
	if (!arr)
		return (1);
	while (p->menv[x])
	{
		if (ft_strnstr_bool(p->menv[x], tok, 0, ft_strlen(tok)))
			x++;
		arr[y++] = p->menv[x++];
	}
	arr[y] = NULL;
	//ft_bzero(p->menv, sizeof(p->menv));
	p->menv = update_free_arr(p->menv, arr);
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
	arr = malloc(sizeof(char *) * (ft_arrlen(p->xport)));
	if (!arr)
		return (1);
	while (p->xport[x])
	{
		if (ft_strnstr_bool(p->xport[x], tok, 11, ft_strlen(tok)))
			x++;
		arr[y++] = p->xport[x++];
	}
	arr[y] = NULL;
	//ft_bzero(p->xport, sizeof(p->xport));
	p->xport = update_free_arr(p->xport, arr);
	return (0);
}

int	unset(t_pipex *p, char **token)
{
	int		x;
	size_t	len;

	x = 0;
	if (!p || !p->menv || !token || !ft_strcmp_bool(token[0], "unset"))
		return (0);
	if (!token[1] || token[1][0] == '$')
		return (perror("not a valid identifier"), 1);
	if (ft_strchr(token[1], '=') != NULL || ft_strcmp_bool(token[1], "_"))
		return (0);
	len = ft_strlen(token[1]);
	while (p->menv[x])
	{
		if (ft_strnstr_bool(p->menv[x], token[1], 0, len))
			return (update_unset(p, token[1]));
		else if (ft_strnstr_bool(p->xport[x], token[1], 0, len))
			return (update_unset_exp(p, token[1]));
		x++;
	}
	return (1);
}
