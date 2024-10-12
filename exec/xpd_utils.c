/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xpd_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbaumeis <lbaumeis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/06 17:42:11 by lbaumeis          #+#    #+#             */
/*   Updated: 2024/10/12 17:42:51 by lbaumeis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	**arrjoin(char **old, char **new)
{
	char	**ret;
	int		x;
	int		y;

	x = 0;
	y = 0;
	ret = ft_calloc((ft_arrlen(old) + ft_arrlen(new) + 1), sizeof(char *));
	if (!ret)
		return (ft_free_double(old), ft_free_double(new), NULL);
	while (ft_arrlen(old) > 0 && old[x])
	{
		ret[x] = ft_strdup(old[x]);
		x++;
	}
	while (ft_arrlen(new) > 0 && new[y])
	{
		ret[x] = ft_strdup(new[y]);
		x++;
		y++;
	}
	return (ft_free_double(old), ft_free_double(new), ret);
}

char	**ft_arrdup(char **s)
{
	int		x;
	char	**arr;

	x = 0;
	if (!s)
		return (NULL);
	arr = ft_calloc(ft_arrlen(s) + 1, sizeof(char *));
	if (!arr)
		return (NULL);
	while (s[x])
	{
		arr[x] = ft_strdup(s[x]);
		x++;
	}
	return (arr);
}

