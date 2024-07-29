/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbaumeis <lbaumeis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 11:15:47 by lbaumeis          #+#    #+#             */
/*   Updated: 2024/07/29 14:51:00 by lbaumeis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	buildins(char **av, t_buildins *vars)
{
	if (vars->cdpath && find_arg(av, "cdpath") >= 0)
		printf("--->CDPATH: %s\n\n", vars->cdpath);
	else
		printf("\n---NO CDPATH---\n\n");
	if (vars->menv && find_arg(av, "menv") >= 0)
	{
		printf("\n--->MENV:\n");
		while (*vars->menv)
		{
			printf("%s\n", *vars->menv);
			vars->menv++;
		}
	}
	else
		printf("\n---NO MENV---\n\n");
	if (vars->menvp && find_arg(av, "menvp") >= 0)
		printf("\n--->MENVP: %s\n\n", vars->menvp);
	else
		printf("\n---NO MENVP---\n\n");
	if (vars->export && find_arg(av, "export") >= 0)
	{
		printf("\n--->EXPORT:\n\n");
		while (*vars->export)
		{
			printf("%s\n", *vars->export);
			vars->export++;
		}
	}
	else
		printf("\n---NO EXPORT---\n\n");
	if (vars->home && find_arg(av, "home") >= 0)
		printf("\n--->HOME: %s\n\n", vars->home);
	else
		printf("\n---NO HOME---\n\n");
	if (vars->oldpwd && find_arg(av, "oldpwd") >= 0)
		printf("\n--->OLDPWD: %s\n\n", vars->oldpwd);
	else
		printf("\n---NO OLDPWD---\n\n");
	if (vars->pwd && find_arg(av, "pwd") >= 0)
		printf("\n--->PWD: %s\n\n", vars->pwd);
	else
		printf("\n---NO PWD---\n\n");
	if (find_arg(av, "cd") >= 0)
	{
		printf("\n--->PWD: %s\n\n", vars->pwd);
		printf("\n--->OLDPWD: %s\n\n", vars->oldpwd);
		if (cd(vars, av) == 1)
			printf("FUCK\n");
		printf("\n--->PWD: %s\n\n", vars->pwd);
		printf("\n--->OLDPWD: %s\n\n", vars->oldpwd);
	}
}

void	pipex(t_pipex *p)
{
	int	c;

	c = 0;
	if (p->cmd_count == 1)
		single_exec(p);
	while (c < p->cmd_count && p->cmd_count > 1)
	{
		p->pid[c] = fork();
		if (p->pid[c] == -1)
			err_free(p, 1);
		if (p->pid[c] == 0)
			do_child(p, &c);
		c++;
		p->x++;
	}
	if (wait(NULL) != -1 && p->cmd_count > 1)
	{
		if (WIFEXITED(p->status))
			p->status = WEXITSTATUS(p->status);
	}
	err_free(p, p->status);
}

int	check_buildins(t_pipex *p)
{
	char	**token;

	token = NULL;
	if (ft_strcmp(p->cmd, "cd"))
	{
		token = malloc(sizeof(char *) * 3);
		if (!token)
			return (-1);
		token[0] = ft_strdup(p->cmd);
		token[1] = ft_strdup(p->av[find_arg(p->av, "cd") + 1]);
		token[2] = NULL;
		return (cd(p->vars, token));
	}
}

int	main(int ac, char **av, char **envp)
{
	t_pipex		p;
	t_buildins	vars;
	
	ft_bzero(&vars, sizeof(t_buildins));
	vars.envp = envp;
	buildins_init(&vars, envp);
	check_args(&p, ac, av, &vars);
	init_p(&p);
	pipex(&p);
	buildins(av, &vars);
	return (0);
}
