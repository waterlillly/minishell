/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbaumeis <lbaumeis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 06:42:08 by lbaumeis          #+#    #+#             */
/*   Updated: 2024/07/15 19:18:00 by lbaumeis         ###   ########.fr       */
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
	processes(&p, envp);
	wait_for_processes(&p);
	return (err_free(&p, p.status), 0);
}
