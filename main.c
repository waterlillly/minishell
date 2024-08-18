/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbaumeis <lbaumeis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 16:39:21 by lbaumeis          #+#    #+#             */
/*   Updated: 2024/08/17 17:30:41 by lbaumeis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void free_parse(t_minishell_p *in)
{
	t_minishell_l	*tmp_l;
	t_minishell_p	*tmp_p;

	while (in && in->next)
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

int	do_stuff(t_pipex *p, t_minishell_p *pars)
{
	int	c;
	
	c = 0;
	if (p->cmd_count > 500)
		return (error("too many commands", 1));
	while (pars && c < p->cmd_count)
	{
		p->pid[c] = fork();
		if (p->pid[c] == -1)
			return (error("fork failed", 1));
		if (p->pid[c] == 0)
		{
			if (execute(p, &c, pars) != 0)
				break ;
		}
		c++;
		pars = pars->next;
	}
	if (wait(NULL) != -1)
	{
		if (WIFEXITED(p->status))
			p->status = WEXITSTATUS(p->status);
	}
	return (p->status);
}

int	main(int ac, char **av, char **envp)
{
	t_pipex			p;
	t_minishell_l	*lex;
	t_minishell_p	*pars;
	t_raw_in		input;
	int				x;
	
	x = 0;
	if (ac < 1 || !av)
	{
		ft_putendl_fd("invalid input", 2);
		exit(EXIT_FAILURE);
	}
	ft_bzero(&p, sizeof(t_pipex));
	lex = NULL;
	pars = NULL;
	first_init(&p, envp);
	while (1)
	{
		ft_bzero(&input, sizeof(t_raw_in));
		get_input(&p, &lex, &pars, &input);
		if (do_stuff(&p, pars) != 0)
			exit_shell(&p, pars, &input, "error");
		free_everything(&p, pars, &input);
	}
	//free_everything(&p, pars, &input);
	exit_shell(&p, pars, &input, "done");
	return (0);
}
