/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 11:14:34 by codespace         #+#    #+#             */
/*   Updated: 2024/08/08 13:15:56 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	set_op(t_raw_in *in, char *line)
{
	int	len;

	len = ft_strlen(line) - 1;
	while (is_sep(" \t", line[len]))
		len--;
	if (line[len] == '|')
		in->open_pipe = true;
	else
		in->open_pipe = false;
}

void	set_hd(t_raw_in *in, char *line)
{
	int	i;
	int j;
	int	k;

	i = in->n_chd - 1;
	in->del_s = ft_realloc_2d(in->del_s, in->n_hd - in->n_chd);
	while (i < in->n_hd - 1 && *line && *(line + 1))
	{
		k = 2;
		j = 0;
		line = skip_q(line);
		if (*line == '<' && *(line + 1) == '<')
		{
			while (is_sep(" \t", *(line + k)))
				k++;
			if (*(line + j + k) == '\"')
			{
				j++;
				while (*(line + j + k) != '\"')
					j++;
				j++;
			}
			else if (*(line + j + k) == '\'')
			{
				j++;
				while (*(line + j + k) != '\'')
					j++;
				j++;
			}
			else
			{
				while (*(line + j + k) && !is_sep(" \t\n\0", *(line + j + k)))
					j++;
			}
			in->del_s[++i] = ft_substr(line, k, j);
			line = line + k + j - 1;
		}
		line++;
	}
	remove_q(in);
}

void	set_first(t_raw_in *in, char *line)
{
	char *tmp;

	tmp = line;
	while (*line)
	{
		line = skip_q(line);
		if (*line == '>')
		{
			in->n_red++;
			if (*(line + 1) == '>')
				line++;
		}
		if (*line == '<')
		{
			if (*(line + 1) == '<')
			{
				in->n_hd++;
				line++;
			}
			else
				in->n_red++;
		}
		if (*line == '|')
			in->n_pipe++;
		if (*line == '$')
			in->n_ds++;
		line++;
	}
	set_hd(in, tmp);
	set_op(in, tmp);
}
