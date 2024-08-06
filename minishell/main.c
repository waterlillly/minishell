/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbaumeis <lbaumeis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 19:06:47 by lbaumeis          #+#    #+#             */
/*   Updated: 2024/08/06 19:32:16 by lbaumeis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int ac, char **av, char **envp)
{
	t_buildins	vars;
	t_raw_in	input;
	t_pipex		p;
	int			x;
	int			c;
	int			i;

	x = 1;
	c = 0;
	init_p(&p);
	ft_bzero(&vars, sizeof(t_buildins));
	vars.envp = envp;
	buildins_init(&vars);
	//MINISHELL
	while (1)
	{
		i = -1;
		init_raw(&input);
		if (!get_line_cnc(&input))
			return (error("syntax error", 0));
		printf("hd:%d\nred:%d\npipe:%d\n", input.n_hd, input.n_red, input.n_pipe);
		while (++i < input.n_hd)
			printf("%d.%s\n%s", i + 1,  input.del_s[i], input.del_str[i]);
		free_raw(&input);
	}
	//PIPEX
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
	//BUILDINS
	while (av[x])
	{
		//if (ft_strcmp(av[x], "cdpath"))
		//	printf("--->CDPATH: %s\n\n", vars.cdpath);
		if (ft_strcmp(av[x], "unset"))
		{
			unset(&vars, av);
			printf("\n--->ENV:\n");
			ft_print_array(vars.menv);
			printf("\n--->EXPORT:\n\n");
			ft_print_array(vars.xport);
		}
		if (ft_strcmp(av[x], "env"))
		{
			printf("\n--->ENV:\n");
			ft_print_array(vars.menv);
		}
		if (ft_strcmp(av[x], "path"))
			printf("\n--->MENVP: %s\n\n", vars.mpath);
		if (ft_strcmp(av[x], "export") && av[x + 1] != NULL)
		{
			printf("\n--->EXPORT:\n\n");
			set_export(&vars, av);
			ft_print_array(vars.xport);
		}
		if (ft_strcmp(av[x], "export") && av[x + 1] == NULL)
		{
			printf("\n--->EXPORT:\n\n");
			ft_print_array(vars.xport);
		}
		if (ft_strcmp(av[x], "home"))
			printf("\n--->HOME: %s\n\n", vars.home);
		if (ft_strcmp(av[x], "oldpwd"))
			printf("\n--->OLDPWD: %s\n\n", vars.oldpwd);
		if (ft_strcmp(av[x], "pwd"))
			printf("\n--->PWD: %s\n\n", vars.pwd);
		
		if (ft_strcmp(av[x], "cd"))
		{
			printf("\nbefore--->PWD: %s", vars.pwd);
			printf("\nbefore--->OLDPWD: %s\n\n", vars.oldpwd);
			if (cd(&vars, av) == 1)
				printf("FUCK\n");
			printf("\nafter--->PWD: %s", vars.pwd);
			printf("\nafter--->OLDPWD: %s\n\n", vars.oldpwd);
		}
		if (ft_strcmp(av[x], "echo"))
		{
			printf("\n--->ECHO:\n");
			echo(&vars, av);
		}
		x++;
	}
	return (0);
}
