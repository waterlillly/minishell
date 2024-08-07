/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbaumeis <lbaumeis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 14:34:21 by lbaumeis          #+#    #+#             */
/*   Updated: 2024/08/07 22:10:11 by lbaumeis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../exec.h"

int	check_empty(char **av)
{
	int	x;

	x = 1;
	while (av[x])
	{
		if (ft_strlen(av[x]) == 0)
			return (1);
		x++;
	}
	return (0);
}

void	init_args(t_pipex *p, t_args **a)
{
	int		i;
	t_args	*new;

	i = 1;
	while (i < p->ac)
	{
		new = NULL;
		new = malloc(sizeof(t_args));
		if (!new)
			return ;
		ft_bzero(new, sizeof(t_args));
		new->arg = p->av[i];
		new->next = NULL;
		if (i == 1)
		{
			new->prev = NULL;
			*a = new;
		}
		else
		{
			new->prev = *a;
			(*a)->next = new;
			(*a) = (*a)->next;
		}
	}
}

void	parse_av(t_pipex *p, t_args **args)
{
	t_args	*a;

	a = *args;
	while (a->next)
	{
		if (ft_strcmp(a->arg, "|"))
			a->pipe = true;
		else if (ft_strcmp(a->arg, "<"))
			a->in = true;
		else if (ft_strcmp(a->arg, "<<"))
			a->hd = true;
		else if (ft_strcmp(a->arg, ">"))
			a->out = true;
		else if (ft_strcmp(a->arg, ">>"))
			a->appd = true;
		else
			a->cmd = true;
		a = a->next;
	}
	*args = a;
}

void	count_args(t_args **args)
{
	t_args	*a;

	a = *args;
	while (a->next)
	//count each arg_type and differ between cmds (execve or buildin)
}

void	check_args(t_pipex *p, int ac, char **av)
{
	t_args	*a;

	a = NULL;
	a = malloc(sizeof(t_args *));
	if (!a)
		return ;
	ft_bzero(&a, sizeof(t_args *));
	if (ac < 2 || check_empty(av))
	{
		ft_putstr_fd("Invalid arguments.\n", 2);
		exit(EXIT_FAILURE);
	}
	p->ac = ac;
	p->av = av;
	p->status = 0;
	init_args(p, &a);
	parse_av(p, &a);
	count_args(&a);
}
