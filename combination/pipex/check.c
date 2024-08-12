/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbaumeis <lbaumeis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 14:34:21 by lbaumeis          #+#    #+#             */
/*   Updated: 2024/08/12 02:20:40 by lbaumeis         ###   ########.fr       */
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

void	check_args(t_pipex *p, int ac, char **av)
{
	if (ac < 2 || check_empty(av))
	{
		ft_putstr_fd("Invalid arguments.\n", 2);
		exit(EXIT_FAILURE);
	}
	p->ac = ac;
	p->av = av;
	p->status = 0;
}
