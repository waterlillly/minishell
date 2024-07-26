/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbaumeis <lbaumeis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 06:42:08 by lbaumeis          #+#    #+#             */
/*   Updated: 2024/07/26 13:09:39 by lbaumeis         ###   ########.fr       */
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
	t_pipex	p;
	int		c;

	c = 0;
	check_args(&p, ac, av, envp);
	init_p(&p);
	if (p.cmd_count == 1)
		single_exec(&p);
	while (c < p.cmd_count && p.cmd_count > 1)
	{
		p.pid[c] = fork();
		if (p.pid[c] == -1)
			err_free(&p, 1);
		if (p.pid[c] == 0)
			do_child(&p, &c);
		c++;
		p.x++;
	}
	if (wait(NULL) != -1 && p.cmd_count > 1)
	{
		if (WIFEXITED(p.status))
			p.status = WEXITSTATUS(p.status);
	}
	err_free(&p, p.status);
	return (0);
}
