/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgardesh <mgardesh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 16:39:21 by lbaumeis          #+#    #+#             */
/*   Updated: 2024/09/08 17:16:31 by mgardesh         ###   ########.fr       */
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
	//restore_fds(p);
	get_input(p, &lex, pars, input);
}

int	do_stuff(t_pipex *p, t_minishell_p *pars)
{
	int	c;
	int	i;
	
	c = 0;
	i = 0;
	while (p && pars && c < p->cmd_count && p->cmd_count > 0)
	{
		p->pid[c] = fork();
		if (p->pid[c] == -1)
			return (perror("fork"), 1);
		if (p->pid[c] == 0)
		{
			p->status = execute(p, c, pars);
			// if (p->status != 0 && kill(p->pid[c], 0) == 0)
			// {
			// 	if (kill(p->pid[c], SIGCHLD) != 0)
			// 		return (perror("kill"), (int)p->status);
			// }
		}
		else
		{
			if (wait(NULL) == -1)
				return (perror("wait"), 1);
			if (WIFEXITED(p->status))
				p->status = WEXITSTATUS(p->status);
		}
		printf("pipe in: %s\n", get_next_line(p->pip[c][0]));
		printf("pipe out: %s\n", get_next_line(p->pip[c][1]));
		printf("std in: %s\n", get_next_line(STDIN_FILENO));
		printf("std out: %s\n", get_next_line(STDOUT_FILENO));
		c++;
		pars = pars->next;
	}
	while (i < p->cmd_count - 1 && waitpid(p->pid[i], NULL, 0) != -1)
	{
		if (WIFEXITED(p->status))
			p->status = WEXITSTATUS(p->status);
		i++;
	}
	return ((int)p->status);
}

bool	run(t_pipex *p, t_raw_in *input, t_minishell_p **pars)
{
	//t_minishell_p	**tmp;

	//tmp = pars;
	refresh_init(p, input, pars);
	if (!*pars)
		return (true);
	if (!p || !input)
		return (false);
	if ((*pars) && (*pars)->str && ft_strcmp_bool((*pars)->str[0], "exit"))
	{
		while ((*pars) && (*pars)->str && (*pars)->next && (*pars)->next->str)
			(*pars) = (*pars)->next;
		//pars = tmp;
		if ((*pars) && (*pars)->str && ft_strcmp_bool((*pars)->str[0], "exit") && !(*pars)->next)
			if (check_exit(p, *pars) == false)
				return (false);
	}
	if (do_stuff(p, *pars) != 0)
		return (false);
	free_everything(p, *pars, input);
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
