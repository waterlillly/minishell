/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbaumeis <lbaumeis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 14:34:21 by lbaumeis          #+#    #+#             */
/*   Updated: 2024/07/22 15:08:53 by lbaumeis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
/*
void	ft_count_args(t_pipex *p)
{
	int	x;
	int	y;

	x = 0;
	y = 1;
	if (ft_strcmp(p->av[y], "here_doc"))
	{
		y++;
		if (ft_strcmp(p->av[y], p->delimiter))
		{
			y++;
			while (!ft_strcmp(p->av[y], p->delimiter))
				y++;
			y++;
		}
	}
	while (p->av[y] && y < p->ac)
	{
		x++;
		y++;
	}
	p->cmd_count = x;
}
*/
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

void	check_args(t_pipex *p, int ac, char **av, char **envp)
{
	if (ac < 5 || check_empty(av))
	{
		ft_putstr_fd("Invalid arguments.\n"
			"./pipex filein cmd1 cmd2 (...) fileout\n"
			"./pipex 'here_doc' <delimiter> cmd1 cmd2 (...) fileout\n", 2);
		exit(EXIT_FAILURE);
	}
	if (!envp)
	{
		perror("envp");
		exit(EXIT_FAILURE);
	}
	p->ac = ac;
	p->av = av;
	p->envp = envp;
}
