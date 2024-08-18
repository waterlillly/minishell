/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_shell.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbaumeis <lbaumeis@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 10:51:09 by codespace         #+#    #+#             */
/*   Updated: 2024/08/14 14:37:41 by lbaumeis         ###   ########.fr       */
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
	int		i;
	int		dq;
	int		sq;

	i = 0;
	*len = 0;
	sq = 0;
	dq = 0;
	while (is_sep(charset, *str) && *str)
		str++;
	if (is_sep("><|", *str))
		return (red_if(str, len));
	if (*str == '$')
		return (ds_skip(str, len, -1));
	while ((!is_sep(charset, str[i]) && str[i]) || (sq % 2 == 1 || dq % 2 == 1))
	{
		if (str[i] == '\"' && sq % 2 == 0)
			dq++;
		if (str[i] == '\'' && dq % 2 == 0)
			sq++;
		if (i != 0 && ((is_sep("<>|", str[i]) && !dq && !sq) || 
		(str[i] == '\"' && dq == 1) || (str[i] == '\'' && sq == 1))) // fix
			break;
		*len = *len + 1;
		i++;
		if ((sq == 2 || dq == 2) && str[i] != '$')
			break;
		else if ((sq == 2 || dq == 2) && str[i] == '$')
		 	return (ds_skip(str, len, i - 1));
	}
	return (str);
}

int	count(char *str, char *charset)
{
	int		len_sub;
	int		len_sep;
	int		i;
	int		dq;
	int		sq;

	len_sub = 0;
	len_sep = 0;
	i = 0;
	while (str[len_sub + len_sep])
	{
		dq = 0;
		sq = 0;
		while (is_sep(charset, str[len_sub + len_sep]) 
			&& str[len_sub + len_sep])
			len_sep++;
		if (!is_sep(charset, str[len_sub + len_sep]) 
			&& str[len_sub + len_sep])
			i++;
		while ((!is_sep(charset, str[len_sub + len_sep]) 
			&& str[len_sub + len_sep]) || (sq % 2 == 1 || dq % 2 == 1))
		{
			if (str[len_sep + len_sub] == '\"' && sq % 2 == 0)
				dq++;
			if (str[len_sep + len_sub] == '\'' && dq % 2 == 0)
				sq++;
			len_sub++;
			if (sq == 2 || dq == 2)
				break;
		}
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
	in->n_words = count(in->input, " \t<>|");
	in->sum = in->n_words + in->n_hd + in->n_pipe + in->n_red + in->n_lessalloc;
	in->out = (char **)ft_calloc(in->sum + 1, sizeof(char *));
	if (!in->out)
		return ;//fix
	while (++i < in->sum)
	{
		in->input = skip_shell(&(in->input[len]), " \t", &len);
		in->out[i] = ft_calloc(len + 1, sizeof(char));
		ft_strncpy(in->out[i], in->input, len);
	}
	in->input = tmp;
}
