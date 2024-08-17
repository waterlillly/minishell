/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbaumeis <lbaumeis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 11:14:34 by codespace         #+#    #+#             */
/*   Updated: 2024/08/17 16:22:59 by lbaumeis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	set_op(t_raw_in *in, char *line)
{
	int	len;

	if (ft_strlen(line) <= 0)
		return ;
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
	in->del_s = (char **)ft_calloc(in->n_hd + 1, sizeof(char *));
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
	remove_dq(in->del_s, in->n_hd);
	remove_sq(in->del_s, in->n_hd);
}

void	set_first(t_raw_in *in, char *line)
{
	char *tmp[2];

	tmp[0] = line;
	while (*line)
	{
		tmp[1] = line;
		line = skip_q(line);
		if (tmp[1] != line && *(line + 1) == '$')
			in->n_lessalloc--;
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
		line++;
	}
	set_hd(in, tmp[0]);
}
