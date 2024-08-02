/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbaumeis <lbaumeis@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/02 12:42:06 by lbaumeis          #+#    #+#             */
/*   Updated: 2024/08/02 18:15:13 by lbaumeis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "buildins.h"
/*
void	new_node(char *part, t_list **ex)
{
	t_list	*e;

	e = NULL;
	e = malloc(sizeof(t_list));
	if (!e)
		err_or("malloc");
	e->data = part;
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

void	linked_list(t_buildins *vars)
{
	int		x;
	char	*part;

	x = 0;
	part = NULL;
	part = ft_strdup(vars->menv[x]);
	if (!part)
		err_or("strdup");
	while (part)
	{
		new_node(part, vars->ex);
		free(part);
		part = NULL;
		x++;
		part = ft_strdup(vars->menv[x]);
		if (!part)
			err_or("strdup");
	}
}

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
bool	is_sorted(t_list *e)
{
	while (e && e->next)
	{
		if (ft_strcmp_org(e->data, e->next->data) <= 0)
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
	*e = a;
}

void	sort_env(t_buildins *vars)
{
	t_list	*e;
	int		x;

	e = NULL;
	fill(vars);
	while (is_sorted(vars->ex) == false)
	{
		e = vars->ex;
		while (e && e->next)
		{
			if (ft_strcmp_org(e->data, e->next->data) <= 0)
				swap(&e);
			else
				e = e->next;
		}
	}
	while(vars->ex->prev)
		vars->ex = vars->ex->prev;
	x = 0;
	while (vars->ex)
	{
		printf("%d-> %s\n", x, vars->ex->data);
		vars->ex = vars->ex->next;
		x++;
	}
}

/*
void	export(t_buildins *vars, char **token)
{
	int	x;
	
	x = find_arg(token, "export");
	
}
*/