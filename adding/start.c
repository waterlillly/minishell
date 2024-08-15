/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbaumeis <lbaumeis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/15 15:23:45 by lbaumeis          #+#    #+#             */
/*   Updated: 2024/08/15 18:04:11 by lbaumeis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	get_input(t_pipex *p)
{
	t_raw_in		input;
	t_minishell_l	*lexed;
	t_minishell_p	*parsed;
	
	ft_bzero(&input, sizeof(t_raw_in));
	init_raw(&input);
	if (!get_line_cnc(&input))
		error("syntax error", 0);
	lexed = lexer(&input);
	parsed = parser(lexed, &input);
	init_p(p, parsed);
	free_raw(&input);
}
