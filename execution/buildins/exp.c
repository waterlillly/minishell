/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exp.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbaumeis <lbaumeis@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/02 16:29:21 by lbaumeis          #+#    #+#             */
/*   Updated: 2024/08/02 17:52:18 by lbaumeis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "buildins.h"

void	add(t_list **head, char *data)
{
	t_list	*node;

	node = NULL;
	node = (t_list *)malloc(sizeof(t_list));
	if (!node)
		err_or("malloc");
	node->data = NULL;
	node->data = ft_strdup(data);
	if (!node->data)
		err_or("strdup");
	node->prev = NULL;
	if (*head)
	{
		node->next = *head;
		(*head)->prev = node;
	}
	else
		node->next = NULL;
	*head = node;
}

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

void	fill(t_buildins *vars)
{
	int		y;
	char	*temp;

	vars->ex = NULL;
	y = ft_arrlen(vars->menv) - 2;
	temp = NULL;
	while (y >= 0 && vars->menv[y])
	{
		temp = strcpy_until(vars->menv[y]);
		if (!temp)
			err_or("idk");
		add(&vars->ex, temp);
		y--;
		free(temp);
		temp = NULL;
	}
}
