/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbaumeis <lbaumeis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 11:14:34 by codespace         #+#    #+#             */
/*   Updated: 2024/08/20 14:37:46 by lbaumeis         ###   ########.fr       */
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
	int	q[2];
	int	j;
	int	i;
	int	k;
	
	q[0] = 0;
	q[1] = 0;
	k = -1;
	in->del_s = (char **)ft_calloc(in->n_hd + 1, sizeof(char *));
	while (k < in->n_hd - 1 && *line && *(line + 1))
	{
		j = 2;
		i = 0;
		if (*line == '<' && *(line + 1) == '<' && !is_oq(*line, &q[0], &q[1]))
		{
			while (*(line + j) && is_sep(" \t", *(line + j)))
				j++;
			while (*(line + j + i) && (is_oq(*(line + i + j), &q[0], &q[1]) || !is_sep(" \t", *(line + j + i))))
				i++;
			in->del_s[++k] = ft_substr(line, j, i);
			line = line + i + j - 1;
		}
		line++;
	}
	remove_q(in->del_s, in->n_hd);
}

void	set_first(t_raw_in *in, char *line)
{
	char	*tmp;
	int		sq;
	int		dq;

	sq = 0;
	dq = 0;
	tmp = line;
	while (*line)
	{
		if (!is_oq(*line, &dq, &sq))
		{
			//if (*(line + 1) == '$')
			//	in->n_lessalloc--;
			if (*line == '>')
			{
				in->n_red++;
				if (*(line + 1) == '>')
					line++;
			}
			else if (*line == '<')
			{
				if (*(line + 1) == '<')
				{
					in->n_hd++;
					line++;
				}
				else
					in->n_red++;
			}
			else if (*line == '|')
				in->n_pipe++;
		}
		line++;
	}
	set_hd(in, tmp);
}
