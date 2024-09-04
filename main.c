/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbaumeis <lbaumeis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 16:39:21 by lbaumeis          #+#    #+#             */
/*   Updated: 2024/09/04 15:59:51 by lbaumeis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int g_signal;

void	free_parse(t_minishell_p *in)
{
	t_minishell_l	*tmp_l;
	t_minishell_p	*tmp_p;

	in = ft_lstfirst_parse(in);
	while (in)
	{
		tmp_p = in->next;
		while (in->redirect)
		{
			tmp_l = in->redirect->next;
			free(in->redirect);
			in->redirect = tmp_l;
		}
		if (in->str)
			free(in->str);
		free(in);
		in = tmp_p;
	}
}

void	refresh_init(t_pipex *p, t_raw_in *input, t_minishell_p **pars)
{
	t_minishell_l	*lex;
	
	lex = NULL;
	restore_fds(p);
	get_input(p, &lex, pars, input);
}

int	do_stuff(t_pipex *p, t_minishell_p *pars)
{
	int	c;
	int	i;
	
	c = 0;
	i = -1;
	while (p && pars && c < p->cmd_count)
	{
		p->pid[c] = fork();
		if (p->pid[c] == -1)
			return (error("fork failed", 1));
		else if (p->pid[c] == 0)
		{
			check(p, pars);
			if (p->status != 1)
				p->status = execute(p, &c, pars);
		}
		else
		{
			close_all(p);
			waitpid(p->pid[c], (int *)p->status, 0);
		}
		c++;
		pars = pars->next;
	}
	while (i++ < p->cmd_count && waitpid(p->pid[i], (int *)p->status, 0) != -1)
	{
		if (WIFEXITED(p->status))
			p->status = WEXITSTATUS(p->status);
	}
	return (p->status);
}

bool	run(t_pipex *p, t_raw_in *input, t_minishell_p **pars)
{
	refresh_init(p, input, pars);
	if (!*pars)
		return (true);
	if (!p || !input)
		return (false);
	if ((*pars)->str && ft_strcmp_bool((*pars)->str[0], "exit"))
	{
		if ((*pars)->str[1])
			check_exit(p, *pars);
		if (p->status == 1)
			return (true);
		return (false);
	}
	else
	{
		p->status = do_stuff(p, *pars);
		if (p->status != 0)
			return (false);
		free_everything(p, *pars, input);
	}
	return (true);
}

int	main(int ac, char **av, char **envp)
{
	t_pipex			p;
	t_minishell_p	*pars;
	t_raw_in		input;
	
	if (ac < 1 || !av)
		return (perror("invalid input"), 1);
	ft_bzero(&p, sizeof(t_pipex));
	ft_bzero(&input, sizeof(t_raw_in));
	pars = NULL;
	signal(SIGINT, &sig_int);
	signal(SIGQUIT, &sig_quit);
	if (first_init(&p, envp) != 0)
	{
		exit_shell(&p, pars, &input, NULL);
		exit(p.status);
	}
	while (run(&p, &input, &pars))
		pars = NULL;
	exit_shell(&p, pars, &input, NULL);
	exit(p.status);
	return (0);
}
