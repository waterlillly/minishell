/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_export.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbaumeis <lbaumeis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/05 14:51:23 by lbaumeis          #+#    #+#             */
/*   Updated: 2024/08/07 14:02:25 by lbaumeis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_strcmp_until(const char *s1, const char *s2)
{
	int	x;

	x = 0;
	if (!s1 || !s2)
		return (0);
	while (s1[x] && s2[x] && s1[x] == s2[x] && s1[x] != '=' && s2[x] != '=')
		x++;
	if (s1[x] == '=' && s2[x] == '=')
		return (0);
	else
		return (s2[x] - s1[x]);
}

char	*create_add_export(t_ms *ms, char *token)
{
	int		x;
	char	*temp;
	char	*temp1;

	x = 0;
	temp = NULL;
	temp1 = NULL;
	if (ft_strchr(token, '='))
	{
		temp = ft_strjoin("declare -x ", strcpy_until(token));
		if (!temp)
			error(ms, "strjoin", 1);
		temp1 = ft_strjoin_free_one(temp, modify_quotes(token));
		if (!temp1)
			error(ms, "strjoin_free_one", 1);
	}
	else
	{
		temp1 = ft_strjoin("declare -x ", token);
		if (!temp1)
			error(ms, "strjoin", 1);
	}
	return (temp1);
}

bool	resorted(char **arr)
{
	int	x;

	x = 0;
	while (arr[x] && arr[x + 1])
	{
		if (ft_strcmp_until(arr[x], arr[x + 1]) >= 0)
			x++;
		else
			return (false);
	}
	return (true);
}

char	**resort_arr(char **arr)
{
	int		x;

	while (!resorted(arr))
	{
		x = 0;
		while (arr[x])
		{
			if (ft_strcmp_until(arr[x], arr[x + 1]) < 0)
				swap(arr, x);
			x++;
		}
	}
	return (arr);
}

void	add_to_env(t_ms *ms, char *add)
{
	int		x;
	char	**arr;

	x = 0;
	arr = NULL;
	arr = malloc(sizeof(char *) * (ft_arrlen(ms->e->menv) + 2));
	if (!arr)
		error(ms, "malloc", 1);
	while (ms->e->menv[x])
	{
		arr[x] = ms->e->menv[x];
		x++;
	}
	arr[x] = add;
	arr[x + 1] = NULL;
	ft_free_double(ms->e->menv);
	ms->e->menv = arr;
}

void	add_to_export(t_ms *ms, char *token)
{
	int		x;
	char	**arr;
	char	*add;

	x = 0;
	arr = NULL;
	add = NULL;
	arr = malloc(sizeof(char *) * (ft_arrlen(ms->e->xport) + 2));
	if (!arr)
		error(ms, "malloc", 1);
	while (ms->e->xport[x])
	{
		arr[x] = ms->e->xport[x];
		x++;
	}
	add = create_add_export(ms, token);
	if (ft_strchr(add, '='))
		add_to_env(ms, ft_substr(add, 11, ft_strlen(add) - 10));
	arr[x] = add;
	arr[x + 1] = NULL;
	ft_free_double(ms->e->xport);
	ms->e->xport = resort_arr(arr);
}
