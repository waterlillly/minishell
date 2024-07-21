/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbaumeis <lbaumeis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 06:42:08 by lbaumeis          #+#    #+#             */
/*   Updated: 2024/07/21 18:07:23 by lbaumeis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
/*
void	minishell(int ac, char **av, t_minishell_p *m)
{
	m->infile = NULL;
	m->str = av;
	m->out = true;
	m->outfile = av[ac - 1];
	m->next = NULL;
	m->prev = NULL;
	m->redir = 0;
	m->redirect = NULL;
}
*/
int	main(int ac, char **av, char **envp)
{
	t_pipex			p;
	//t_minishell_p	*m;

	//m = NULL;
	//minishell(ac, av, m);
	check_args(ac, av, envp);
	//p.m = m;
	init_p(&p, ac, av, envp);
	create_pipes(&p);
	while (p.c < p.cmd_count)
	{
		p.pid[p.c] = fork();
		if (p.pid[p.c] == -1)
			err_free(&p, 1);
		if (p.pid[p.c] == 0)
			do_child(&p, envp);
		p.c++;
		p.x++;
	}
	if (wait(NULL) != -1)
	{
		if (WIFEXITED(p.status))
			p.status = WEXITSTATUS(p.status);
	}
	err_free(&p, p.status);
	return (0);
}
