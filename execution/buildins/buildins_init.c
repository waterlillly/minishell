/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buildins_init.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbaumeis <lbaumeis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/27 13:48:57 by lbaumeis          #+#    #+#             */
/*   Updated: 2024/07/28 15:36:48 by lbaumeis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "buildins.h"

void	buildins_init(t_buildins *vars)
{
	get_menv(vars);
	get_home(vars);
	get_cdpath(vars);
	get_menvp(vars);
	get_pwd(vars);
	get_oldpwd(vars);
	//export
}

int	find_arg(char **s, char *a)
{
	int	x;

	x = 0;
	if (!s || !a)
		return (-1);
	while (s[x])
	{
		if (ft_strcmp(s[x], a))
			return (x);
		x++;
	}
	return (-1);
}

int	main(int ac, char **av, char **envp)
{
	t_buildins	vars;

	if (ac < 2)
	{
		printf("not enough args\n");
		return (0);
	}
	ft_bzero(&vars, sizeof(t_buildins));
	vars.envp = envp;
	buildins_init(&vars);
	if (vars.cdpath && find_arg(av, "cdpath") >= 0)
		printf("--->CDPATH: %s\n\n", vars.cdpath);
	else
		printf("\n---NO CDPATH---\n\n");
	
	if (vars.menv && find_arg(av, "menv") >= 0)
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
	if (vars.menvp && find_arg(av, "menvp") >= 0)
		printf("\n--->MENVP: %s\n\n", vars.menvp);
	else
		printf("\n---NO MENVP---\n\n");
	if (vars.export && find_arg(av, "export") >= 0)
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
	if (vars.home && find_arg(av, "home") >= 0)
		printf("\n--->HOME: %s\n\n", vars.home);
	else
		printf("\n---NO HOME---\n\n");
	if (vars.oldpwd && find_arg(av, "oldpwd") >= 0)
		printf("\n--->OLDPWD: %s\n\n", vars.oldpwd);
	else
		printf("\n---NO OLDPWD---\n\n");
	if (vars.pwd && find_arg(av, "pwd") >= 0)
		printf("\n--->PWD: %s\n\n", vars.pwd);
	else
		printf("\n---NO PWD---\n\n");
	if (find_arg(av, "cd") >= 0)
	{
		printf("\n--->PWD: %s\n\n", vars.pwd);
		printf("\n--->OLDPWD: %s\n\n", vars.oldpwd);
		if (cd(&vars, av) == 1)
			printf("FUCK\n");
		printf("\n--->PWD: %s\n\n", vars.pwd);
		printf("\n--->OLDPWD: %s\n\n", vars.oldpwd);
	}
	return (0);
}
