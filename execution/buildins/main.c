/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbaumeis <lbaumeis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 10:58:31 by lbaumeis          #+#    #+#             */
/*   Updated: 2024/08/06 16:36:22 by lbaumeis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "buildins.h"

int	main(int ac, char **av, char **envp)
{
	int			x;
	t_buildins	vars;

	x = 1;
	if (ac < 1)
		err_or("not enough args");
	ft_bzero(&vars, sizeof(t_buildins));
	vars.envp = envp;
	buildins_init(&vars);
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
