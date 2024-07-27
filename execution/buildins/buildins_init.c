/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buildins_init.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbaumeis <lbaumeis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/27 13:48:57 by lbaumeis          #+#    #+#             */
/*   Updated: 2024/07/27 18:13:37 by lbaumeis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "buildins.h"

void	buildins_init(t_buildins *vars)
{
	get_menv(vars);
	get_menvp(vars);
	get_oldpwd(vars);
	get_home(vars);
	//export
	//cdpath
}

int	main(int ac, char **av, char **envp)
{
	t_buildins	vars;

	if (ac != 8)
		return (-1);
	ft_bzero(&vars, sizeof(t_buildins));
	vars.envp = envp;
	buildins_init(&vars);
	if (vars.cdpath && ft_strcmp(av[1], "cdpath"))
		printf("--->CDPATH: %s\n\n", vars.cdpath);
	else
		printf("\n---NO CDPATH---\n\n");
	if (vars.menv && ft_strcmp(av[2], "menv"))
	{
		printf("\n--->MENV:\n");
		while (*vars.menv)
		{
			printf("%s\n", *vars.menv);
			vars.menv++;
		}
	}
	else
		printf("\n---NO MENV---\n\n");
	if (vars.menvp && ft_strcmp(av[3], "menvp"))
		printf("\n--->MENVP: %s\n\n", vars.menvp);
	else
		printf("\n---NO MENVP---\n\n");
	if (vars.export && ft_strcmp(av[4], "export"))
	{
		printf("\n--->EXPORT:\n\n");
		while (*vars.export)
		{
			printf("%s\n", *vars.export);
			vars.export++;
		}
	}
	else
		printf("\n---NO EXPORT---\n\n");
	if (vars.home && ft_strcmp(av[5], "home"))
		printf("\n--->HOME: %s\n\n", vars.home);
	else
		printf("\n---NO HOME---\n\n");
	if (vars.oldpwd && ft_strcmp(av[6], "oldpwd"))
		printf("\n--->OLDPWD: %s\n\n", vars.oldpwd);
	else
		printf("\n---NO OLDPWD---\n\n");
	if (vars.pwd && ft_strcmp(av[7], "pwd"))
		printf("\n--->PWD: %s\n\n", vars.pwd);
	else
		printf("\n---NO PWD---\n\n");
	return (0);
}
