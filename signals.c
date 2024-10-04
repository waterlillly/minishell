/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgardesh <mgardesh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 14:54:25 by mgardesh          #+#    #+#             */
/*   Updated: 2024/10/01 20:00:49 by mgardesh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

volatile sig_atomic_t g_signal = 0;

void	set_mode_s(t_pipex *p, int c)
{
	p->mode = c;
	sig_init(p, 0);
}

void	sig_init(t_pipex *p, int hd)
{
	if (hd)
		(signal(SIGQUIT, SIG_IGN), signal(SIGINT, &sig_int_hd));
	else if (p->mode == CHILD)
		(signal(SIGINT, &sig_int_child), signal(SIGQUIT, &sig_quit_child));
	else if (p->mode == INTER)
		(signal(SIGINT, &sig_int), signal(SIGQUIT, SIG_IGN));
	else if (p->mode == LEVEL)
		(signal(SIGINT, SIG_IGN), signal(SIGQUIT, SIG_IGN));
	else
		(signal(SIGINT, &sig_int), signal(SIGQUIT, SIG_IGN));
		
}

void	sig_int_hd(int num)
{
	g_signal = 130;
	ioctl(STDIN_FILENO, TIOCSTI, "\n");
	(void)num;
}

void	sig_quit_child(int num)
{
	g_signal = 131;
	ft_putendl_fd("\nQUIT COREDUMP", 2);
	//rl_replace_line("", 0);
	//rl_on_new_line();
	//rl_redisplay();
	(void)num;
}

void	sig_int_child(int num)
{
	g_signal = 130;
	//ft_putstr_fd("\n", 2);
	//rl_replace_line("", 0);
	//rl_on_new_line();
	//rl_redisplay();
	(void)num;
}

void	sig_int(int num)
{
	g_signal = 130;
	ft_putstr_fd("\n", 2);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
	(void)num;
}

void	sig_quit(int num)
{
	g_signal = 131;
	//ft_putendl_fd("\n", 2);
	//rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
	(void)num;
}