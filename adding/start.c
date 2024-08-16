/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbaumeis <lbaumeis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/15 15:23:45 by lbaumeis          #+#    #+#             */
/*   Updated: 2024/08/16 16:54:20 by lbaumeis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	get_input(t_pipex *p, t_minishell_l **lex, t_minishell_p **pars)
{
	t_raw_in		input;
	
	ft_bzero(&input, sizeof(t_raw_in));
	init_raw(&input);
	if (!get_line_cnc(&input))
		error("syntax error", 0);
	*lex = lexer(&input);
	*pars = parser(*lex, &input);
	//print_parsed(pars);
	init_p(p, *pars);
	//free_raw(&input);
}
