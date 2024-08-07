/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbaumeis <lbaumeis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 16:39:21 by lbaumeis          #+#    #+#             */
/*   Updated: 2024/08/07 22:10:18 by lbaumeis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

int	main(int ac, char **av, char **envp)
{
	t_pipex	p;
	int		c;

	c = 0;
	ft_bzero(&p, sizeof(t_pipex));
	check_args(&p, ac, av);
	init_p(&p, envp);
	if (p.cmd_count > 500)
		error(&p, "too many commands", p.status);
	if (p.cmd_count == 1)
		single_exec(&p);
	while (c < p.cmd_count && p.cmd_count > 1)
	{
		p.pid[c] = fork();
		if (p.pid[c] == -1)
			error(&p, "fork failed", p.status);
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
	err_free(&p);
	return (p.status);
}
