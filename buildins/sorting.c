/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sorting.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbaumeis <lbaumeis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/18 16:54:40 by lbaumeis          #+#    #+#             */
/*   Updated: 2024/09/13 14:37:51 by lbaumeis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

bool	sorted(char **arr)
{
	int	x;

	x = 0;
	while (arr && arr[x] && arr[x + 1])
	{
		if (ft_strcmp(arr[x], arr[x + 1]) >= 0)
			x++;
		else
			return (false);
	}
	return (true);
}

void	swap(char **arr, int x)
{
	char	*temp;

	if (!arr || !arr[x] || !arr[x + 1])
		return ;
	temp = arr[x];
	arr[x] = arr[x + 1];
	arr[x + 1] = temp;
}

void	sort_arr(t_pipex *p, char **arr)
{
	int		x;

	if (!p || !p->menv)
		return ;
	copy_arr_env(p, arr);
	if (!arr)
		return ;
	while (arr && !sorted(arr))
	{
		x = 0;
		while (arr && arr[x] && arr[x + 1])
		{
			if (ft_strcmp(arr[x], arr[x + 1]) < 0)
				swap(arr, x);
			x++;
		}
	}
}

bool	resorted(char **arr)
{
	int	x;

	x = 0;
	while (arr && arr[x] && arr[x + 1])
	{
		if (ft_strcmp_until(arr[x], arr[x + 1]) >= 0)
			x++;
		else
			return (false);
	}
	return (true);
}

void	resort_arr(char **arr)
{
	int		x;

	if (!arr)
		return ;
	while (!resorted(arr))
	{
		x = 0;
		while (arr && arr[x] && arr[x + 1])
		{
			if (ft_strcmp_until(arr[x], arr[x + 1]) < 0)
				swap(arr, x);
			x++;
		}
	}
}
