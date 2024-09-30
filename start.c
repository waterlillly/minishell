/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbaumeis <lbaumeis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/15 15:23:45 by lbaumeis          #+#    #+#             */
/*   Updated: 2024/09/30 22:29:15 by lbaumeis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	get_input(t_pipex *p, t_minishell_l **lex, t_minishell_p **pars, t_raw_in *input)
{
	int	stat;

	init_raw(input);
	stat = get_line_cnc(input, p);
	if (!stat)
		error("syntax error", 0);
	if (stat == 1)
	{
		*lex = lexer(input);
		if (!*lex)
			return (exit_shell(NULL, NULL, NULL, "FAILED"));
		*pars = parser(*lex, input);
		//print_parsed(*pars);
		if (!*pars)
			return (exit_shell(NULL, NULL, NULL, "FAILED"));
		xpd(p, *pars);
		//print_ps(*pars);
		init_p(p, *pars);
	}
}

void	print_ps(t_minishell_p *pars)
{
	int	i;
	t_minishell_l *tmp;
	while (pars)
	{
		tmp = pars->redirect;
		i = -1;
		while (pars->ps[++i])
			printf("str%d.:%s\n", i + 1, pars->ps[i]);
		if (tmp)
		{
			while (tmp)
			{
				printf("token:%d\nfile:%s\n", tmp->token, tmp->input);
				tmp = tmp->next;
			}
		}
		else
			printf("NULL\n");
		printf("\n***********\n");
		pars = pars->next;
	}
}
