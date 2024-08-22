/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgardesh <mgardesh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/15 15:23:45 by lbaumeis          #+#    #+#             */
/*   Updated: 2024/08/22 19:27:50 by mgardesh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	get_input(t_pipex *p, t_minishell_l **lex, t_minishell_p **pars, t_raw_in *input)
{
	int	stat;

	init_raw(input);
	stat = get_line_cnc(input);
	if (!stat)
		error("syntax error", 0);
	if (stat == 1)
	{
		*lex = lexer(input);
		if (!*lex)
			return (exit_shell(NULL, NULL, NULL, "FAILED"));
		*pars = parser(*lex, input);
		if (!*pars)
			return (exit_shell(NULL, NULL, NULL, "FAILED"));
		init_p(p, *pars);
	}
}
