/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbaumeis <lbaumeis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 16:39:21 by lbaumeis          #+#    #+#             */
/*   Updated: 2024/08/23 14:22:58 by lbaumeis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int g_signal;

void free_parse(t_minishell_p *in)
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

int	check(t_pipex *p, t_minishell_p *pars, int *c)
{
	if (p->cmd_count > 500)
	{
		ft_putendl_fd("too many commands", 2);
		p->status = 1;
		return (1);
	}
	else if (p && pars && pars->str && p->cmd_count == 1
		&& is_buildin(pars->str[0]))
	{
		p->status = execute(p, c, pars);
		return (1);
	}
	return (0);
}

int	do_stuff(t_pipex *p, t_minishell_p *pars)
{
	int	c;
	
	c = 0;
	while (p && pars && c < p->cmd_count)
	{
		if (check(p, pars, &c))
			return (p->status);
		p->pid[c] = fork();
		if (p->pid[c] == -1)
			return (error("fork failed", 1));
		if (p->pid[c] == 0)
		{
			p->status = execute(p, &c, pars);
			if (p->status != 0)
				return (p->status);
		}
		c++;
		pars = pars->next;
	}
	while (wait(NULL) != -1)
	{
		if (WIFEXITED(p->status))
			p->status = WEXITSTATUS(p->status);
	}
	return (p->status);
}

bool	run(t_pipex *p, t_raw_in *input, t_minishell_p *pars)
{
	refresh_init(p, input, &pars);
	if (!pars)
		return (true);//continue ;
	if (pars->str && ft_strcmp_bool(pars->str[0], "exit"))
	{
		if (pars->str[1])
			p->status = ft_atoi(pars->str[1]);
		return (false);
	}
	else
	{
		p->status = do_stuff(p, pars);
		if (p->status != 0)
			return (false);
		free_everything(p, pars, input);
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
	if (first_init(&p, envp) != 0)
	{
		exit_shell(&p, pars, &input, NULL);
		exit(p.status);
	}
	while (1)
	{
		if (run(&p, &input, pars) == false)
		{
			exit_shell(&p, pars, &input, NULL);
			exit(p.status);
		}
		pars = NULL;
	}
	return (0);
}
