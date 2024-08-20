/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbaumeis <lbaumeis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 16:39:21 by lbaumeis          #+#    #+#             */
/*   Updated: 2024/08/20 20:06:34 by lbaumeis         ###   ########.fr       */
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
			p->status = execute(p, &c, pars);//if funct != 0->return p->status
		else
		{
			if (wait(&p->status) == -1)
				return (perror("waitpid"), exit(EXIT_FAILURE), -1);
			if (WIFEXITED(p->status))
				p->status = WEXITSTATUS(p->status);
		}
		c++;
		pars = pars->next;
	}
	return (p->status);
}

void	refresh_init(t_pipex *p, t_raw_in *input, t_minishell_p **pars)
{
	t_minishell_l	*lex;
	
	lex = NULL;
	restore_fds(p);
	free_everything(p, *pars, input);
	get_input(p, &lex, pars, input);
}

int	main(int ac, char **av, char **envp)
{
	t_pipex			p;
	t_minishell_p	*pars;
	t_raw_in		input;
	bool			run;
	
	if (ac < 1 || !av)
		return (perror("invalid input"), 1);
	ft_bzero(&p, sizeof(t_pipex));
	ft_bzero(&input, sizeof(t_raw_in));
	pars = NULL;
	first_init(&p, envp);
	run = true;
	while (1)
	{
		refresh_init(&p, &input, &pars);
		if (pars && pars->str && ft_strcmp_bool(pars->str[0], "exit"))
		{
			if (pars->str[1])
				p.status = ft_atoi(pars->str[1]);
			run = false;
		}
		else
		{
			p.status = do_stuff(&p, pars);
			if (p.status != 0)
				run = false;
		}
		if (run == false)
		{
			exit_shell(&p, pars, &input, NULL);
			exit(p.status);
		}
	}
	return (0);
}
