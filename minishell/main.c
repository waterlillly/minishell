/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbaumeis <lbaumeis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 19:06:47 by lbaumeis          #+#    #+#             */
/*   Updated: 2024/08/07 16:09:35 by lbaumeis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(void)
{
	t_raw_in	in;
	int			i;

	ft_bzero(&in, sizeof(t_raw_in));
	init_raw(&in);
	while (1)
	{
		i = -1;
		if (!get_line_cnc(&in))
			exit(EXIT_FAILURE);
		printf("hd:%d\nred:%d\npipe:%d\n", in.n_hd, in.n_red, in.n_pipe);
		while (++i < in.n_hd)
			printf("\nIDK:\n%d.%s\n%s\n", i + 1,  in.del_s[i], in.del_str[i]);
	}
	//return (error(&ms, NULL, 0));
}

/*
int	main(int ac, char **av, char **envp)
{
	t_ms		ms;
	int			x;
	int			c;
	int			i;

	x = 1;
	c = 0;
	if (ac < 1)
		error(&ms, NULL, 1);
	ft_bzero(&ms, sizeof(t_ms));
	init_mini_part1(&ms, envp, ac, av);
	while (1)
	{
		i = -1;
		if (!get_line_cnc(&ms))
			error(&ms, "syntax error", 1);
		printf("hd:%d\nred:%d\npipe:%d\n", ms.in->n_hd, ms.in->n_red, ms.in->n_pipe);
		while (++i < ms.in->n_hd)
		{
			printf("\nIDK:\n%d.%s\n%s\n", i + 1,  ms.in->del_s[i], ms.in->del_str[i]);
			if (find_arg(av, "|") >= 0 || find_arg(av, "<") >= 0 || find_arg(av, ">") >= 0 || find_arg(av, ">>") >= 0)
			{
				if (ms.e->cmd_count == 1)
					single_exec(&ms);
				while (c < ms.e->cmd_count && ms.e->cmd_count > 1)
				{
					ms.e->pid[c] = fork();
					if (ms.e->pid[c] == -1)
						error(&ms, "fork failed", 1);
					if (ms.e->pid[c] == 0)
						do_child(&ms, &c);
					c++;
					ms.e->x++;
				}
			}
			if (ft_strcmp(av[i], "unset"))
			{
				unset(&ms, ms.in->del_s);
				printf("\n--->ENV:\n");
				ft_print_array(ms.e->menv);
				printf("\n--->EXPORT:\n\n");
				ft_print_array(ms.e->xport);
			}
			if (ft_strcmp(av[i], "env"))
			{
				printf("\n--->ENV:\n");
				ft_print_array(ms.e->menv);
			}
			if (ft_strcmp(av[i], "path"))
				printf("\n--->MENVP: %s\n\n", ms.e->mpath);
			if (ft_strcmp(av[i], "export") && ms.in->del_s[x + 1] != NULL)
			{
				printf("\n--->EXPORT:\n\n");
				set_export(&ms, ms.in->del_s);
				ft_print_array(ms.e->xport);
			}
			if (ft_strcmp(av[i], "export") && ms.in->del_s[x + 1] == NULL)
			{
				printf("\n--->EXPORT:\n\n");
				ft_print_array(ms.e->xport);
			}
			if (ft_strcmp(av[i], "home"))
				printf("\n--->HOME: %s\n\n", ms.e->home);
			if (ft_strcmp(av[i], "oldpwd"))
				printf("\n--->OLDPWD: %s\n\n", ms.e->oldpwd);
			if (ft_strcmp(av[i], "pwd"))
				printf("\n--->PWD: %s\n\n", ms.e->pwd);
			
			if (ft_strcmp(av[i], "cd"))
			{
				printf("\nbefore--->PWD: %s", ms.e->pwd);
				printf("\nbefore--->OLDPWD: %s\n\n", ms.e->oldpwd);
				if (cd(&ms, ms.in->del_s) == 1)
					printf("FUCK\n");
				printf("\nafter--->PWD: %s", ms.e->pwd);
				printf("\nafter--->OLDPWD: %s\n\n", ms.e->oldpwd);
			}
			if (ft_strcmp(av[i], "echo"))
			{
				printf("\n--->ECHO:\n");
				echo(&ms, ms.in->del_s);
			}
		}
		if (wait(NULL) != -1 && ms.e->cmd_count > 1)
		{
			if (WIFEXITED(ms.e->status))
				ms.e->status = WEXITSTATUS(ms.e->status);
		}
		if (i >= ms.in->n_hd)
			break ;
	}
	return (error(&ms, NULL, 0));
}
*/