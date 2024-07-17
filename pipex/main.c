/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbaumeis <lbaumeis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 06:42:08 by lbaumeis          #+#    #+#             */
/*   Updated: 2024/07/17 18:07:36 by lbaumeis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int ac, char **av, char **envp)
{
	t_pipex	p;

	if (ac < 5)
		exit(EXIT_FAILURE);//msg
	init_p(&p, ac, av);
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
