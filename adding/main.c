/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbaumeis <lbaumeis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 16:39:21 by lbaumeis          #+#    #+#             */
/*   Updated: 2024/08/16 18:59:16 by lbaumeis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void free_parse(t_minishell_p *in)
{
	t_minishell_l	*tmp_l;
	t_minishell_p	*tmp_p;

	while (in)
	{
		tmp_p = in->next;
		while (in->redirect)
		{
			tmp_l = in->redirect->next;
			free (in->redirect);
			in->redirect = tmp_l;
		}
		if (in->str)
			free(in->str);
		free(in);
		in = tmp_p;
	}
}

int	main(int ac, char **av, char **envp)
{
	t_pipex			p;
	t_minishell_l	*lex;
	t_minishell_p	*pars;
	t_raw_in		input;
	int				c;
	
	if (ac < 1 || !av)
	{
		ft_putendl_fd("invalid input", 2);
		exit(EXIT_FAILURE);
	}
	ft_bzero(&p, sizeof(t_pipex));
	lex = NULL;
	pars = NULL;
	if (!envp)
		backup_env(&p);
	else
		get_menv(&p, envp);
	first_init(&p);
	while (1)
	{
		ft_bzero(&input, sizeof(t_raw_in));
		get_input(&p, &lex, &pars, &input);
		c = 0;
		if (p.cmd_count > 500)
			error("too many commands", p.status);
		while (pars && c < p.cmd_count)////////////////////////////
		{
			p.pid[c] = fork();
			if (p.pid[c] == -1)
				error("fork failed", p.status);
			if (p.pid[c] == 0)
				execute(&p, &c, pars);//do_child(&p, &c);
			c++;
			pars = pars->next;
		}
		if (wait(NULL) != -1)//////////////////////
		{
			if (WIFEXITED(p.status))
				p.status = WEXITSTATUS(p.status);
		}
		//if (dup2(STDOUT_FILENO, p.copy_stdout) == -1)
		//	return (p.status);//error(p, "dup2 failed", p->status);
		//if (dup2(STDIN_FILENO, p.copy_stdin) == -1)
		//	return (p.status);//error(p, "dup2 failed", p->status);
		err_free(&p);
		free_parse(pars);
		free_raw(&input);
	}
	err_free(&p);
	return (p.status);
}
