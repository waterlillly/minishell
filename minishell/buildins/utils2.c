/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbaumeis <lbaumeis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/04 13:23:55 by lbaumeis          #+#    #+#             */
/*   Updated: 2024/08/07 12:28:57 by lbaumeis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	find_str_part(char **str, char *tok)
{
	int	x;
	int	y;

	x = 0;
	while (str[x])
	{
		y = 0;
		while (tok[y] == str[x][y])
			y++;
		if (tok[y] == '\0' && str[x][y] == '=')
			return (x);
		x++;
	}
	return (-1);
}

char	*strcpy_until(char *v_part)
{
	char	*ret;
	int		c;
	int		x;

	ret = NULL;
	c = 0;
	x = 0;
	while (v_part[c] != '=')
		c++;
	ret = malloc(sizeof(char) * (c + 1));
	if (!ret)
		return (NULL);
	while (x < c)
	{
		ret[x] = v_part[x];
		x++;
	}
	ret[x] = '\0';
	return (ret);
}

char	**copy_arr_env(t_ms *ms)
{
	int		x;
	char	**arr;

	x = 0;
	arr = NULL;
	arr = malloc(sizeof(char *) * (ft_arrlen(ms->e->menv) + 1));
	if (!arr)
		return (NULL);
	while (ms->e->menv[x])
	{
		arr[x] = strcpy_until(ms->e->menv[x]);
		x++;
	}
	arr[x] = NULL;
	return (arr);
}

bool	check_quotes(char *token)
{
	int		x;
	bool	q1;

	x = 0;
	q1 = false;
	while (token[x] && token[x] != '=')
		x++;
	x++;
	if (token[x] == '\"' || token[x] == '\'')
		q1 = true;
	x++;
	while (token[x])
	{
		if ((token[x] == '\"' || token[x] == '\'') && token[x + 1] == '\0'
			&& q1 == true)
				return (true);
		x++;
	}
	return (false);
}

bool	valid_env(t_ms *ms, char *tok)
{
	int	x;
	int	y;

	x = 0;
	while (ms->e->menv[x])
	{
		y = 0;
		while (tok[y] == ms->e->menv[x][y])
		{
			if (tok[y] == '=' && ms->e->menv[x][y] == '=')
				return (true);
			y++;
		}
		x++;
	}
	return (false);
}
