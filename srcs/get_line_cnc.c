/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_line_cnc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 19:25:32 by codespace         #+#    #+#             */
/*   Updated: 2024/08/12 13:56:58 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// fix the del_str

void	get_hd(t_raw_in *in)
{
	in->del_str = (char **)ft_calloc(in->n_hd + 1, sizeof(char *));
	if (in->n_hd)
	{
		while (in->n_chd < in->n_hd)
		{
			in->line = readline("heredoc> ");
			if (!ft_strcmp(in->del_s[in->n_chd], in->line))
			{
				in->n_chd++;
				free(in->line);
				continue;
			}
			in->del_str[in->n_chd] = ft_strcat(in->del_str[in->n_chd], in->line);
			in->del_str[in->n_chd] = ft_strcat(in->del_str[in->n_chd], "\n");
			free(in->line);
		}
	}
}

void	get_pipe(t_raw_in *in)
{
	if (in->open_pipe)
	{
		in->line = readline("command> ");
		if (!check_syntax(in->line))
			return ((void)error("idk", 1));
		in->input = ft_strcat(in->input, in->line);
		set_first(in, in->line);
	}
}

int	get_line_cnc(t_raw_in *in)
{
	in->line = readline("this is a legit minishell> ");
	set_op(in, in->line);
	if (!check_syntax(in->line) || in->open_pipe)
		return (0);
	in->input = ft_strcat(in->input, in->line);
	set_first(in, in->line);
	free(in->line);
	get_hd(in);
	return (1);
}