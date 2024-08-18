/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbaumeis <lbaumeis@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/04 18:54:32 by lbaumeis          #+#    #+#             */
/*   Updated: 2024/08/18 16:19:02 by lbaumeis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	update_unset(t_pipex *p, char *tok)
{
	int		x;
	int		y;
	char	**arr;

	x = 0;
	y = 0;
	if (!p || !tok || !p->menv)
		return ;
	arr = NULL;
	arr = malloc(sizeof(char *) * (ft_arrlen(p->menv)));
	if (!arr)
		return ;
	while (p->menv[x])
	{
		if (ft_strnstr_bool(p->menv[x], tok, 0, ft_strlen(tok)))
			x++;
		arr[y++] = p->menv[x++];
	}
	arr[y] = NULL;
	ft_bzero(p->menv, sizeof(p->menv));
	p->menv = arr;
	update_unset_exp(p, tok);
}

void	update_unset_exp(t_pipex *p, char *tok)
{
	int		x;
	int		y;
	char	**arr;

	x = 0;
	y = 0;
	if (!p || !tok || !p->xport)
		return ;
	arr = NULL;
	arr = malloc(sizeof(char *) * (ft_arrlen(p->xport)));
	if (!arr)
		return ;
	while (p->xport[x])
	{
		if (ft_strnstr_bool(p->xport[x], tok, 11, ft_strlen(tok)))
			x++;
		arr[y++] = p->xport[x++];
	}
	arr[y] = NULL;
	ft_bzero(p->xport, sizeof(p->xport));
	p->xport = arr;
}

void	unset(t_pipex *p, char **token)
{
	int		x;
	size_t	len;

	x = 0;
	if (!p || !p->menv || !token || !ft_strcmp_bool(token[0], "unset"))
		return ;
	if (!token[1] || token[1][0] == '$')
		return ;//error(p, "not a valid identifier", p->status);
	if (ft_strchr(token[1], '=') != NULL || ft_strcmp_bool(token[1], "_"))
		return ;
	len = ft_strlen(token[1]);
	while (p->menv[x])
	{
		if (ft_strnstr_bool(p->menv[x], token[1], 0, len))
			update_unset(p, token[1]);
		else if (ft_strnstr_bool(p->xport[x], token[1], 0, len))
			update_unset_exp(p, token[1]);
		x++;
	}
}
