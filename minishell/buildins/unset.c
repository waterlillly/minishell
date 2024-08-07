/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbaumeis <lbaumeis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/04 18:54:32 by lbaumeis          #+#    #+#             */
/*   Updated: 2024/08/07 14:09:22 by lbaumeis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	update_unset(t_ms *ms, char *tok)
{
	int		x;
	int		y;
	char	**arr;

	x = 0;
	y = 0;
	arr = NULL;
	arr = malloc(sizeof(char *) * (ft_arrlen(ms->e->menv)));
	if (!arr)
		error(ms, "malloc", 1);
	while (ms->e->menv[x])
	{
		if (ft_strnstr_bool(ms->e->menv[x], tok, 0, ft_strlen(tok)))
			x++;
		arr[y++] = ms->e->menv[x++];
	}
	arr[y] = NULL;
	ft_bzero(ms->e->menv, sizeof(ms->e->menv));
	ms->e->menv = arr;
	update_unset_exp(ms, tok);
}

void	update_unset_exp(t_ms *ms, char *tok)
{
	int		x;
	int		y;
	char	**arr;

	x = 0;
	y = 0;
	arr = NULL;
	arr = malloc(sizeof(char *) * (ft_arrlen(ms->e->xport)));
	if (!arr)
		error(ms, "malloc", 1);
	while (ms->e->xport[x])
	{
		if (ft_strnstr_bool(ms->e->xport[x], tok, 11, ft_strlen(tok)))
			x++;
		arr[y++] = ms->e->xport[x++];
	}
	arr[y] = NULL;
	ft_bzero(ms->e->xport, sizeof(ms->e->xport));
	ms->e->xport = arr;
}

void	unset(t_ms *ms, char **token)
{
	int		x;
	int		y;
	size_t	len;

	y = 0;
	x = find_arg(token, "unset") + 1;
	if (x == 0)
		return ;
	//if (token[x][0] == '$')
	//	err_or("not a valid identifier");
	printf("token after unset: %s\n", token[x]);
	if (ft_strchr(token[x], '=') != NULL || ft_strcmp(token[x], "_"))
		return ;
	len = ft_strlen(token[x]);
	while (ms->e->menv[y])
	{
		if (ft_strnstr_bool(ms->e->menv[y], token[x], 0, len) == true)
			update_unset(ms, token[x]);
		else if (ft_strnstr_bool(ms->e->xport[y], token[x], 0, len) == true)
			update_unset_exp(ms, token[x]);
		y++;
	}
}
