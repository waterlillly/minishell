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
	temp = ft_strjoin_free_one(temp1, get_env(p, arr[y]));
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
	int		y;
	
	y = 0;
	if (!p || !p->menv)
		return (1);
	arr = NULL;
	arr = sort_arr(p);
	if (!arr)
		return (1);
	p->xport = malloc(sizeof(char *) * (ft_arrlen(arr) + 1));
	if (!p->xport)
		return (1);
	while (arr && arr[y])
	{
		p->xport[y] = ft_strjoin("declare -x ", exp_whole(p, arr, y));
		if (!p->xport[y])
			return (1);
		y++;
	}
	p->xport[y] = NULL;
	ft_free_double(arr);
	return (0);
}

char	*create_add_export(char *token)
{
	char	*temp;
	char	*temp1;

	temp = NULL;
	temp1 = NULL;
	if (!token)
		return (NULL);
	if (ft_strchr(token, '='))
	{
		temp = ft_strjoin(strcpy_until(token), add_quotes(token));
		if (!temp)
			return (NULL);
		temp1 = ft_strjoin("declare -x ", temp);
		free(temp);
		temp = NULL;
		if (!temp1)
			return (NULL);
	}
	else
	{
		temp1 = ft_strjoin("declare -x ", token);
		if (!temp1)
			return (NULL);
	}
	return (temp1);
}

void	add_to_env(t_pipex *p, char *add)
{
	int		x;
	char	**arr;

	x = 0;
	arr = NULL;
	if (!p || !add || !p->menv)
		return ;
	arr = malloc(sizeof(char *) * (ft_arrlen(p->menv) + 2));
	if (!arr)
		return ;
	while (p->menv[x])
	{
		arr[x] = p->menv[x];
		x++;
	}
	arr[x] = add;
	arr[x + 1] = NULL;
	p->menv = arr;
}

void	add_to_export(t_pipex *p, char *token)
{
	int		x;
	char	**arr;

	x = -1;
	arr = NULL;
	if (!p || !token || !p->xport)
		return ;
	arr = malloc(sizeof(char *) * (ft_arrlen(p->xport) + 2));
	if (!arr)
		return ;
	while (p->xport[++x])
		arr[x] = p->xport[x];
	arr[x] = create_add_export(token);
	if (ft_strchr(arr[x], '='))
		add_to_env(p, token);
	arr[x + 1] = NULL;
	p->xport = resort_arr(arr);
}
