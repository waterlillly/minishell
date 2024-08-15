/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbaumeis <lbaumeis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 16:39:21 by lbaumeis          #+#    #+#             */
/*   Updated: 2024/08/15 18:02:32 by lbaumeis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int ac, char **av, char **envp)
{
	t_pipex			p;
	int				c;
	
	if (ac > 4 || av[1] != NULL || !envp)
	{
		ft_putendl_fd("invalid input", 2);
		exit(EXIT_FAILURE);
	}
	ft_bzero(&p, sizeof(t_pipex));
	first_init(&p, envp);
	while (1)
	{
		get_input(&p);
		c = 0;
		if (p.cmd_count > 500)
			error("too many commands", p.status);
		if (p.cmd_count == 1)
			single_exec(&p);
		while (c < p.cmd_count && p.cmd_count > 1)
		{
			p.pid[c] = fork();
			if (p.pid[c] == -1)
				error("fork failed", p.status);
			if (p.pid[c] == 0)
				execute(&p, &c);//do_child(&p, &c);
			c++;
			p.pars = p.pars->next;
		}
		if (wait(NULL) != -1 && p.cmd_count > 1)
		{
			if (WIFEXITED(p.status))
				p.status = WEXITSTATUS(p.status);
		}
		err_free(&p);
	}
	err_free(&p);
	return (p.status);
}
