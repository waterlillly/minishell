/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_line_cnc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 19:25:32 by codespace         #+#    #+#             */
/*   Updated: 2024/08/08 12:07:39 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// fix the del_str

void	get_hd(t_raw_in *in)
{
	in->del_str = ft_realloc_2d(in->del_str, in->n_hd - in->n_chd);
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
	if (!check_syntax(in->line))
		return (0);
	in->input = ft_strcat(in->input, in->line);
	set_first(in, in->line);
	free(in->line);
	while (in->open_pipe || in->n_chd < in->n_hd)
	{
		get_hd(in);
		get_pipe(in);
	}
	return (1);
}