/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbaumeis <lbaumeis@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/02 16:29:21 by lbaumeis          #+#    #+#             */
/*   Updated: 2024/08/04 20:05:53 by lbaumeis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "buildins.h"

bool	sorted(char **arr)
{
	int	x;

	x = 0;
	while (arr[x] && arr[x + 1])
	{
		if (ft_strcmp_org(arr[x], arr[x + 1]) >= 0)
			x++;
		else
			return (false);
	}
	return (true);
}

void	swap(char **arr, int x)
{
	char	*temp;

	temp = arr[x];
	arr[x] = arr[x + 1];
	arr[x + 1] = temp;
}

char	**sort_arr(char **arr)
{
	//char	**arr;
	int		x;

	//arr = copy_arr_env(vars);
	while (!sorted(arr))
	{
		x = 0;
		while (arr[x])
		{
			if (ft_strcmp_org(arr[x], arr[x + 1]) < 0)
				swap(arr, x);
			x++;
		}
	}
	return (arr);
}

char	*exp_whole(t_buildins *vars, char **arr, int y)
{
	char	*temp;
	char	*temp1;

	temp = NULL;
	temp1 = NULL;
	temp = ft_strjoin(arr[y], "=\"");
	if (!temp)
		return (NULL);
	//temp1 = ft_strjoin_free_one(temp, "");
	//if (!temp1)
	//	return (NULL);
	temp1 = ft_strjoin_free_one(temp, get_env(vars, arr[y]));
	if (!temp1)
		return (NULL);
	temp = ft_strjoin_free_one(temp1, "\"");
	if (!temp)
		return (NULL);
	return (temp1);
}

void	combine_export(t_buildins *vars)
{
	char	**arr;
	int		y;
	
	arr = NULL;
	arr = sort_arr(copy_arr_env(vars));
	y = 0;
	vars->export = malloc(sizeof(char *) * (ft_arrlen(arr) + 1));
	if (!vars->export)
		err_or("malloc");
	while (arr[y])
	{
		vars->export[y] = ft_strjoin("declare -x ", exp_whole(vars, arr, y));
		if (!vars->export[y])
			err_or("exp_whole");
		y++;
	}
	vars->export[y] = NULL;
	ft_free_double(arr);
}
