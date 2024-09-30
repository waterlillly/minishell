/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbaumeis <lbaumeis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 16:39:21 by lbaumeis          #+#    #+#             */
/*   Updated: 2024/09/30 14:08:48 by lbaumeis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//volatile sig_atomic_t	g_signal = 0;
extern int	g_signal;

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
	get_input(p, &lex, pars, input);
}

int	do_stuff(t_pipex *p, int c, t_minishell_p *pars)
{
	int	i;

	i = 0;
	while (p && pars && c < p->cmd_count && p->cmd_count > 0)
	{
		if (check(p, pars) != 0)
			return (0);
		if (p->cmd_count == 1 && is_buildin(pars->ps[0]) && !pars->redirect)
		{
			p->status = do_this(p, pars);
			return (0);
		}
		else
		{
			p->pid[c] = fork();
			if (p->pid[c] == -1)
				return (perror("fork"), 1);
			if (p->pid[c] == 0)
			{
				execute(p, c, pars);
				if (kill(p->pid[c], 0) == 0)
				{
					if (kill(p->pid[c], SIGCHLD) != 0)
						return (perror("kill"), (int)p->status);
					return (1);
				}
				return (0);
			}
		}
		c++;
		pars = pars->next;
	}
	close_all(p);
	while (i < p->cmd_count && p->cmd_count > 0 && waitpid(p->pid[i], NULL, 0) != -1)
	{
		if (WIFEXITED(p->status))
			p->status = WEXITSTATUS(p->status);
		i++;
	}
	return ((int)p->status);
}

bool	run(t_pipex *p, t_raw_in *input, t_minishell_p **pars)
{
	int	c;

	c = 0;
	refresh_init(p, input, pars);
	if (!*pars)
		return (true);
	if (!p || !input)
		return (false);
	if (check_exit(p, &c, pars) == false)
		return (false);
	if ((*pars) && !ft_strcmp_bool((*pars)->ps[0], "exit"))
	{
		if (do_stuff(p, c, *pars) != 0)
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
