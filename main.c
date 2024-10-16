/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbaumeis <lbaumeis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 16:39:21 by lbaumeis          #+#    #+#             */
/*   Updated: 2024/10/16 15:28:36 by lbaumeis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	refresh_init(t_pipex *p, t_raw_in *input, t_minishell_p **pars)
{
	t_minishell_l	*lex;

	lex = NULL;
	get_input(p, &lex, pars, input);
}

int	do_stuff(t_pipex *p, int c, t_minishell_p *pars)
{
	int			i;
	char		*s;

	i = 0;
	s = NULL;
	while (p && pars && c < p->cmd_count && p->cmd_count > 0)
	{
		if (ft_strcmp_bool(pars->ps[0], "exit"))
		{
			s = check_exit(p, pars);
			if (p->exit == true)
				ft_putendl_fd("exit", 2);
			if (s)
				ft_putendl_fd(s, 2);
			free(s);
			if (p->exit == true)
				return (1);
		}
		else if (p->cmd_count == 1 && is_buildin(pars->ps[0]) && !pars->redirect)
		{
			p->status = do_this(p, pars);
			return (0);
		}
		else
		{
			set_mode_s(p, CHILD);
			p->pid[c] = fork();
			if (p->pid[c] == -1)
				return (perror("fork"), 1);
			if (p->pid[c] == 0)
			{
				remove_q(pars->str, pars->str_len);
				if (ft_strcmp_bool("./minishell", pars->str[0]))
					set_mode_s(p, INTER);
				execute(p, c, pars);
				exit(p->status);
			}
			remove_q(pars->str, pars->str_len);
			if (ft_strcmp_bool("./minishell", pars->str[0]))
				set_mode_s(p, LEVEL);
		}
		c++;
		pars = pars->next;
	}
	close_all(p);
	while (i < p->cmd_count && p->cmd_count > 0 && waitpid(p->pid[i], &p->status, 0) != -1)
	{
		if (WIFEXITED(p->status))
			p->status = WEXITSTATUS(p->status);
		i++;
	}
	return (0);
}

bool run(t_pipex *p, t_raw_in *input, t_minishell_p **pars)
{
	int	c;

	c = 0;
	g_signal = 0;
	set_mode_s(p, 1);
	refresh_init(p, input, pars);
	if ((!*pars || !(*pars)->ps || !*(*pars)->ps || !**(*pars)->ps) && 
		(!*pars || !(*pars)->redirect) && input->exit == 0)
		return (free_everything(NULL, *pars, input), true);
	
	else if (!*pars && input->exit == 1)
		return (false);
	if (!p || !input)
		return (false);
	// if (check_exit(p, &c, pars) == false)
	// 	return (false);
	// if ((*pars))// && !ft_strcmp_bool((*pars)->ps[0], "exit"))
	// {
	if (do_stuff(p, c, *pars) != 0)// || p->exit == true)
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
	if (!envp)
		return (perror("no env"), 1);
	ft_bzero(&p, sizeof(t_pipex));
	ft_bzero(&input, sizeof(t_raw_in));
	sig_init(&p, 0);
	pars = NULL;
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
