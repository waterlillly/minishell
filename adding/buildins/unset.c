/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbaumeis <lbaumeis@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/04 18:54:32 by lbaumeis          #+#    #+#             */
/*   Updated: 2024/08/14 14:35:33 by lbaumeis         ###   ########.fr       */
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
	arr = NULL;
	arr = malloc(sizeof(char *) * (ft_arrlen(p->menv)));
	if (!arr)
		return ;//error(p, "malloc", p->status);
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
	arr = NULL;
	arr = malloc(sizeof(char *) * (ft_arrlen(p->xport)));
	if (!arr)
		return ;//error(p, "malloc", p->status);
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
	int		y;
	size_t	len;

	y = 0;
	x = 1;
	if (token[x][0] == '$')
		return ;//error(p, "not a valid identifier", p->status);
	if (ft_strchr(token[x], '=') != NULL || ft_strcmp(token[x], "_"))
		return ;
	len = ft_strlen(token[x]);
	while (p->menv[y])
	{
		if (ft_strnstr_bool(p->menv[y], token[x], 0, len) == true)
			update_unset(p, token[x]);
		else if (ft_strnstr_bool(p->xport[y], token[x], 0, len) == true)
			update_unset_exp(p, token[x]);
		y++;
	}
}
