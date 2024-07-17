/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbaumeis <lbaumeis@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 06:42:08 by lbaumeis          #+#    #+#             */
/*   Updated: 2024/07/17 13:11:11 by lbaumeis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int ac, char **av, char **envp)
{
	t_pipex	p;

	if (ac < 5)
		exit(EXIT_FAILURE);
	init_p(&p, ac, av);
	create_pipes(&p);
	while (p.c < p.cmd_count)
	{
		p.pid[p.c] = fork();
		if (p.pid[p.c] == -1)
			err_free(&p, 1);
		if (p.pid[p.c] == 0)
			do_child(&p, envp);
		wait(NULL);
		if (WIFEXITED(p.status))
			p.status = WEXITSTATUS(p.status);
		printf("process: %d\n", p.c);
		p.c++;
		p.x++;
	}
	if (wait(NULL) != -1)
	{
		if (WIFEXITED(p.status))
			p.status = WEXITSTATUS(p.status);
	}
	printf("HERE\n");
	err_free(&p, p.status);
	return (0);
}
