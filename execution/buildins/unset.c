/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbaumeis <lbaumeis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/04 18:54:32 by lbaumeis          #+#    #+#             */
/*   Updated: 2024/08/07 11:32:21 by lbaumeis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "buildins.h"

void	update_unset(t_buildins *vars, char *tok)
{
	int		x;
	int		y;
	char	**arr;

	x = 0;
	y = 0;
	arr = NULL;
	arr = malloc(sizeof(char *) * (ft_arrlen(vars->menv)));
	if (!arr)
		error("malloc");
	while (vars->menv[x])
	{
		if (ft_strnstr_bool(vars->menv[x], tok, 0, ft_strlen(tok)))
			x++;
		arr[y++] = vars->menv[x++];
	}
	arr[y] = NULL;
	ft_bzero(vars->menv, sizeof(vars->menv));
	vars->menv = arr;
	update_unset_exp(vars, tok);
}

void	update_unset_exp(t_buildins *vars, char *tok)
{
	int		x;
	int		y;
	char	**arr;

	x = 0;
	y = 0;
	arr = NULL;
	arr = malloc(sizeof(char *) * (ft_arrlen(vars->xport)));
	if (!arr)
		error("malloc");
	while (vars->xport[x])
	{
		if (ft_strnstr_bool(vars->xport[x], tok, 11, ft_strlen(tok)))
			x++;
		arr[y++] = vars->xport[x++];
	}
	arr[y] = NULL;
	ft_bzero(vars->xport, sizeof(vars->xport));
	vars->xport = arr;
}

void	unset(t_buildins *vars, char **token)
{
	int		x;
	int		y;
	size_t	len;

	y = 0;
	x = find_arg(token, "unset") + 1;
	if (x == 0)
		return ;
	//if (token[x][0] == '$')
	//	error("not a valid identifier");
	printf("token after unset: %s\n", token[x]);
	if (ft_strchr(token[x], '=') != NULL || ft_strcmp(token[x], "_"))
		return ;
	len = ft_strlen(token[x]);
	while (vars->menv[y])
	{
		if (ft_strnstr_bool(vars->menv[y], token[x], 0, len) == true)
			update_unset(vars, token[x]);
		else if (ft_strnstr_bool(vars->xport[y], token[x], 0, len) == true)
			update_unset_exp(vars, token[x]);
		y++;
	}
}
