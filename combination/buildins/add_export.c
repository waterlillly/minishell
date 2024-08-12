/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_export.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbaumeis <lbaumeis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/05 14:51:23 by lbaumeis          #+#    #+#             */
/*   Updated: 2024/08/12 17:19:57 by lbaumeis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../exec.h"

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

char	*create_add_export(char *token)//t_pipex *p, 
{
	char	*temp;
	char	*temp1;

	temp = NULL;
	temp1 = NULL;
	if (ft_strchr(token, '='))
	{
		temp = ft_strjoin(strcpy_until(token), add_quotes(token));
		if (!temp)
			return (NULL);
		temp1 = ft_strjoin("declare -x ", temp);
		free(temp);
		temp = NULL;
		if (!temp1)
			return (NULL);//error(p, "strjoin", p->status);
	}
	else
	{
		temp1 = ft_strjoin("declare -x ", token);
		if (!temp1)
			return (NULL);//error(p, "strjoin", p->status);
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

void	add_to_env(t_pipex *p, char *add)
{
	int		x;
	char	**arr;

	x = 0;
	arr = NULL;
	arr = malloc(sizeof(char *) * (ft_arrlen(p->menv) + 2));
	if (!arr)
		return ;//error(p, "malloc", p->status);
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
	char	*add;

	x = 0;
	arr = NULL;
	add = NULL;
	if (!token)
		return ;
	arr = malloc(sizeof(char *) * (ft_arrlen(p->xport) + 2));
	if (!arr)
		return ;//error(p, "malloc", p->status);
	while (p->xport[x])
	{
		arr[x] = p->xport[x];
		x++;
	}
	add = create_add_export(token);
	printf("add: %s\n", add);
	if (ft_strchr(add, '='))
		add_to_env(p, token);
	arr[x] = add;
	arr[x + 1] = NULL;
	p->xport = resort_arr(arr);
}
