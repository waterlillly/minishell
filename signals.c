/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgardesh <mgardesh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 14:54:25 by mgardesh          #+#    #+#             */
/*   Updated: 2024/09/30 19:13:58 by mgardesh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

volatile sig_atomic_t g_signal = 0;

void	sig_init(t_pipex *p)
{
	if (p->mode == CHILD)
		signal(SIGINT, &sig_int);
	else if (p->mode == INTER)
		signal(SIGQUIT, SIG_IGN);
	else if (p->mode == HD)
		signal(SIGQUIT, SIG_IGN);
		
}

void	sig_int(int num)
{
	g_signal = 130;
	ft_putendl_fd("\n", 2);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
	(void)num;
}

void	sig_quit(int num)
{
	g_signal = 131;
	//ft_putendl_fd("\n", 2);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
	(void)num;
}