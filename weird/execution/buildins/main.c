/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbaumeis <lbaumeis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 11:13:04 by lbaumeis          #+#    #+#             */
/*   Updated: 2024/07/29 15:53:51 by lbaumeis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "buildins.h"

int	main(int ac, char **av, char **envp)
{
	t_buildins	vars;
	int			x;

	if (ac < 2)
	{
		printf("not enough args\n");
		return (0);
	}
	x = 1;
	ft_bzero(&vars, sizeof(t_buildins));
	buildins_init(&vars, envp);
	while (av[x])
	{
		if (ft_strcmp(av[x], "cdpath"))
			printf("--->CDPATH: %s\n\n", vars.cdpath);
		else if (ft_strcmp(av[x], "menv"))
		{
			printf("\n--->MENV:\n");
			while (*vars.menv)
			{
				printf("%s\n", *vars.menv);
				vars.menv++;
			}
		}
		else if (ft_strcmp(av[x], "menvp"))
			printf("\n--->MENVP: %s\n\n", vars.menvp);
		else if (ft_strcmp(av[x], "export"))
		{
			printf("\n--->EXPORT:\n\n");
			while (*vars.export)
			{
				printf("%s\n", *vars.export);
				vars.export++;
			}
		}
		else if (ft_strcmp(av[x], "home"))
			printf("\n--->HOME: %s\n\n", vars.home);
		else if (ft_strcmp(av[x], "oldpwd"))
			printf("\n--->OLDPWD: %s\n\n", vars.oldpwd);
		else if (ft_strcmp(av[x], "pwd"))
			printf("\n--->PWD: %s\n\n", vars.pwd);
		else if (ft_strcmp(av[x], "cd"))
		{
			if (cd(&vars, av) == 1)
				printf("FUCK\n");
		}
		x++;
	}
	return (0);
}
