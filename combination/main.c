/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbaumeis <lbaumeis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 16:39:21 by lbaumeis          #+#    #+#             */
/*   Updated: 2024/08/12 18:29:13 by lbaumeis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

int	main(int ac, char **av, char **envp)
{
	t_pipex	p;
	char	*str;
	int		c;

	if (ac > 4 || av[1] != NULL)
	{
		ft_putendl_fd("invalid input", 2);
		exit(EXIT_FAILURE);
	}
	ft_bzero(&p, sizeof(t_pipex));
	first_init(&p, envp);
	str = NULL;
	str = readline("minishell> ");
	add_history(str);
	while (1)//!ft_strcmp(str, "exit")
	{
		c = 0;
		p.av = ft_split(str, '\"');
		free(str);
		str = NULL;
		if (!p.av)
			error(&p, "split failed", 1);
		p.ac = ft_arrlen(p.av);
		
		init_p(&p);
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
		str = readline("minishell> ");
		add_history(str);
	}
	err_free(&p);
	return (p.status);
}
