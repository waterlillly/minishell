/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exp.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbaumeis <lbaumeis@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/02 16:29:21 by lbaumeis          #+#    #+#             */
/*   Updated: 2024/08/02 21:41:05 by lbaumeis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "buildins.h"

char	*strcpy_until(char *v_part)
{
	int		eq;
	char	*ret;
	int		c;
	int		x;

	eq = '=';
	ret = NULL;
	c = 0;
	x = 0;
	while (v_part[c] != eq)
		c++;
	ret = malloc(sizeof(char) * (c + 1));
	if (!ret)
		err_or("malloc");
	while (x < c)
	{
		ret[x] = v_part[x];
		x++;
	}
	ret[x] = '\0';
	return (ret);
}

char	**copy_arr_env(t_buildins *vars)
{
	int		x;
	char	**arr;

	x = 0;
	arr = NULL;
	arr = malloc(sizeof(char *) * (ft_arrlen(vars->menv) + 1));
	if (!arr)
		return (NULL);
	while (vars->menv[x])
	{
		arr[x] = strcpy_until(vars->menv[x]);
		x++;
	}
	arr[x] = NULL;
	return (arr);
}

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

char	**sort_arr(t_buildins *vars)
{
	char	**arr;
	int		x;

	arr = copy_arr_env(vars);
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
	temp = ft_strjoin(arr[y], "=");
	if (!temp)
		return (NULL);
	temp1 = ft_strjoin_free_one(temp, "\"");
	if (!temp1)
		return (NULL);
	temp = ft_strjoin_free_one(temp1, get_env(vars, arr[y]));
	if (!temp)
		return (NULL);
	temp1 = ft_strjoin_free_one(temp, "\"");
	if (!temp1)
		return (NULL);
	return (temp1);
}

void	combine_export(t_buildins *vars)
{
	char	**arr;
	int		y;
	
	arr = sort_arr(vars);
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
