/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_shell.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgardesh <mgardesh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 10:51:09 by codespace         #+#    #+#             */
/*   Updated: 2024/08/22 19:04:06 by mgardesh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_sep(char *charset, char c)
{
	while (*charset)
	{
		if (*charset == c)
			return (1);
		charset++;
	}
	return (0);
}

char	*red_if(char *str, int *len)
{
	if ((*str == '<' && *(str + 1) == '<') || (*str == '>' && *(str + 1) == '>'))
		return (*len = 2, str);
	return (*len = 1, str);
}

char	*ds_skip(char *str, int *len, int i)
{
	int dq;
	int	sq;

	dq = 0;
	sq = 0;
	while (str[++i] && (!is_sep(" \t", str[i]) || (sq % 2 == 1 || dq % 2 == 1)))
	{
		if (str[i] == '\'' && dq == 0)
			sq++;
		if (str[i] == '\"' && sq == 0)
			dq++;
		*len = *len + 1;
		if (sq == 2 || dq == 2)
			break;
	}
	if (str[i] && !is_sep(" \t", str[i]) && str[++i] && str[i] == '$')
		return (ds_skip(str, len, i - 1));
	return (str);
}

char	*skip_shell(char *str, char *charset, int *len)
{
	int	j;
	int	dq;
	int	sq;
	
	j = 0;
	sq = 0;
	dq = 0;
	*len = 0;
	while (*str && is_sep(charset, *str))
		str++;
	if (is_sep("<>|", *(str + *len)))
		return (red_if(str, len));
	while (*(str + *len) && (!is_sep(charset, *(str + *len)) || j))
	{
		j = is_oq(*(str + *len), &dq, &sq);
		if (is_sep("<>|", *(str + *len)) && !j)
			break;
		*len = *len + 1;
	}
	return (str);
}

int	count(char *str, char *charset)
{
	int		ls;
	int		lw;
	int		i;
	int		dq;
	int		sq;

	ls = 0;
	lw = 0;
	dq = 0;
	sq = 0;
	i = 0;
	while (str[ls + lw])
	{
		while (str[ls + lw] && is_sep(charset, str[ls + lw]))
			lw++;
		if (str[ls + lw] && !is_sep(charset, str[ls + lw]))
			i++;
		while (str[ls + lw] && (is_oq(str[ls + lw], &dq, &sq) || !is_sep(charset, str[ls + lw])))
			ls++;
	}
	return (i);
}

void	ft_split_shell(t_raw_in *in)
{
	int	i;
	int	len;
	char	*tmp;
	
	len = 0;
	tmp = in->input;
	i = -1;
	in->n_words = count(in->input, " \t><|");
	in->sum = in->n_words + in->n_hd + in->n_pipe + in->n_red;
	in->out = (char **)ft_calloc(in->sum + 1, sizeof(char *));
	if (!in->out)
		return (exit_shell(NULL, NULL, in, "ALLOC FAILED"));
	while (++i < in->sum)
	{
		in->input = skip_shell(&(in->input[len]), " \t", &len);
		in->out[i] = ft_calloc(len + 1, sizeof(char));
		if (!in->out[i])
			return (exit_shell(NULL, NULL, in, "ALLOC FAILED"));
		ft_strncpy(in->out[i], in->input, len);
	}
	in->input = tmp;
}
