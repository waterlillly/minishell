/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xport.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbaumeis <lbaumeis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/02 16:29:21 by lbaumeis          #+#    #+#             */
/*   Updated: 2024/08/05 12:24:13 by lbaumeis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*exp_whole(t_pipex *p, char **arr, int y)
{
	char	*temp;
	char	*temp1;

	temp = NULL;
	temp1 = NULL;
	if (!p || !arr || !arr[y])
		return (NULL);
	temp = ft_strjoin(arr[y], "=");
	if (!temp)
		return (NULL);
	temp1 = ft_strjoin_free_one(temp, "\"");
	if (!temp1)
		return (NULL);
	temp = ft_strjoin_free_both(temp1, get_env(p, arr[y]));
	if (!temp)
		return (NULL);
	temp1 = ft_strjoin_free_one(temp, "\"");
	if (!temp1)
		return (NULL);
	return (temp1);
}

int	combine_export(t_pipex *p)
{
	char	**arr;
	char	*temp;
	int		y;
	
	y = -1;
	if (!p || !p->menv)
		return (1);
	arr = (char **)ft_calloc((ft_arrlen(p->menv) + 1), sizeof(char *));
	if (!arr)
		return (1);
	sort_arr(p, arr);
	if (!arr)
		return (1);
	p->xport = (char **)ft_calloc((ft_arrlen(arr) + 1), sizeof(char *));
	if (!p->xport)
		return (ft_free_2d(arr), 1);
	while (arr && arr[++y])
	{
		temp = NULL;
		temp = exp_whole(p, arr, y);
		p->xport[y] = ft_strjoin("declare -x ", temp);
		(free(temp), temp = NULL);
		if (!p->xport[y])
			return (ft_free_2d(arr), 1);
	}
	return (ft_free_2d(arr), 0);
}

char	*create_add_export(char *token)
{
	char	*temp;
	char	*temp1;
	char	*temp2;
	char	*temp3;
	char	*temp4;
	int		x;

	temp = NULL;
	temp1 = NULL;
	temp2 = NULL;
	temp3 = NULL;
	temp4 = NULL;
	x = 0;
	if (token && ft_strchr(token, '='))
	{
		while (token[x] && token[x] != '=')
			x++;
		temp = ft_strjoin_free_one(strcpy_until(token), "=");
		temp4 = ft_substr(token, x + 1, ft_strlen(token) - (x + 1));
		temp2 = add_quotes(temp4);
		temp3 = ft_strjoin_free_both(temp, temp2);
		if (!temp3)
			return (NULL);
		temp1 = ft_strjoin_free_both(ft_strdup("declare -x "), temp3);
	}
	else if (token)
		temp1 = ft_strjoin("declare -x ", token);
	return (temp1);
}

int	add_to_env(t_pipex *p, char *add)
{
	int		x;
	char	**arr;

	x = 0;
	if (!p || !add || !p->menv)
		return (0);
	arr = ft_calloc((ft_arrlen(p->menv) + 2), sizeof(char *));
	if (!arr)
		return (1);
	while (p->menv[x])
	{
		arr[x] = ft_strdup(p->menv[x]);
		if (!arr[x])
			return (ft_free_2d(arr), 1);
		x++;
	}
	arr[x] = ft_strdup(add);
	if (!arr[x])
		return (ft_free_2d(arr), 1);
	p->menv = update_free_arr(p->menv, arr);
	if (!p->menv)
		return (1);
	return (0);
}

int	add_to_export(t_pipex *p, char *token)
{
	int		x;
	char	**arr;

	x = 0;
	if (!p || !token || !p->xport)
		return (0);
	arr = ft_calloc((ft_arrlen(p->xport) + 2), sizeof(char *));
	if (!arr)
		return (1);
	while (p->xport[x])
	{
		arr[x] = ft_strdup(p->xport[x]);
		if (!arr[x])
			return (ft_free_2d(arr), 1);
		x++;
	}
	arr[x] = create_add_export(token);
	if (!arr[x] || (ft_strchr(arr[x], '=') && add_to_env(p, token) != 0))
		return (ft_free_2d(arr), 1);
	resort_arr(arr);
	p->xport = update_free_arr(p->xport, arr);
	if (!p->xport)
		return (1);
	return (0);
}
