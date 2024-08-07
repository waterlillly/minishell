/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbaumeis <lbaumeis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/04 18:54:32 by lbaumeis          #+#    #+#             */
/*   Updated: 2024/08/07 17:11:21 by lbaumeis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../exec.h"

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
		error(p, "malloc", p->status);
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
		error(p, "malloc", p->status);
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
	x = find_arg(token, "unset") + 1;
	if (x == 0)
		return ;
	//if (token[x][0] == '$')
	//	error(p, "not a valid identifier");
	printf("token after unset: %s\n", token[x]);
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
