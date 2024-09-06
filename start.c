/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbaumeis <lbaumeis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/15 15:23:45 by lbaumeis          #+#    #+#             */
/*   Updated: 2024/09/06 19:18:20 by lbaumeis         ###   ########.fr       */
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
		init_p(p, *pars);
	}
}
