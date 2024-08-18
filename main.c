/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbaumeis <lbaumeis@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 16:39:21 by lbaumeis          #+#    #+#             */
/*   Updated: 2024/08/18 12:10:55 by lbaumeis         ###   ########.fr       */
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

void	refresh_init(t_pipex *p, t_raw_in *input, t_minishell_p **pars)
{
	t_minishell_l	*lex;
	
	lex = NULL;
	free_everything(p, *pars, input);
	get_input(p, &lex, pars, input);
}

int	main(int ac, char **av, char **envp)
{
	t_pipex			p;
	t_minishell_p	*pars;
	t_raw_in		input;
	
	if (ac < 1 || !av)
	{
		ft_putendl_fd("invalid input", 2);
		exit(EXIT_FAILURE);
	}
	ft_bzero(&p, sizeof(t_pipex));
	ft_bzero(&input, sizeof(t_raw_in));
	pars = NULL;
	first_init(&p, envp);
	while (1)
	{
		refresh_init(&p, &input, &pars);
		if (do_stuff(&p, pars) != 0)
			exit_shell(&p, pars, &input, "error");
	}
	exit_shell(&p, pars, &input, "done");
	return (0);
}
