/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbaumeis <lbaumeis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/02 12:42:06 by lbaumeis          #+#    #+#             */
/*   Updated: 2024/08/02 16:30:32 by lbaumeis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "buildins.h"

void	new_node(t_buildins *vars, t_list **ex, int x)
{
	t_list	*e;

	e = NULL;
	e = malloc(sizeof(t_list));
	if (!e)
		err_or("malloc");
	e->index = x;
	e->data = ft_strdup(vars->menv[x]);
	if (!e->data)
		err_or("strdup");
	e->prev = NULL;
	if (*ex)
	{
		e->next = *ex;
		(*ex)->prev = e;
	}
	else
		e->next = NULL;
	*ex = e;
}

void	linked_list(t_buildins *vars, t_list **ex)
{
	int		x;

	x = 0;
	while (x <= ft_arrlen(vars->menv))
	{
		new_node(vars, ex, x);
		x++;
	}
}

/*
void	copy_menv(t_buildins *vars, char **arr)
{
	while (*vars->menv)
	{
		*arr = ft_strdup(*vars->menv);
		arr++;
		vars->menv++;
	}
	*arr = NULL;
}
*/
bool	is_sorted(t_list **ex)
{
	t_list	*e;

	e = *ex;
	while (e->next)
	{
		if (ft_strcmp_org(e->data, e->next->data, '=') <= 0)
			return (false);
		e = e->next;
	}
	return (true);
}

void	swap(t_list **e)
{
	t_list	*a;
	t_list	*b;
	t_list	*temp;

	a = *e;
	b = (*e)->next;
	if (!a || !b)
		return ;
	temp = b->next;
	a->next = temp;
	b->next = a;
	a->prev = b;
	b->prev = NULL;
	if (temp)
		temp->prev = a;
	*e = b;
}

void	sort_env(t_buildins *vars)
{
	t_list	*e;
	t_list	*head;
	
	e = NULL;
	printf("HERE\n");
	linked_list(vars, &e);
	head = e;
	while (is_sorted(&e) == false)
	{
		e = head;
		while (e->next)
		{
			if (ft_strcmp_org(e->data, e->next->data, '=') <= 0)
				swap(&e);
			e = e->next;
		}
	}
	
}

/*
void	export(t_buildins *vars, char **token)
{
	int	x;
	
	x = find_arg(token, "export");
	
}
*/