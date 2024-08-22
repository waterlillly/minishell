/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgardesh <mgardesh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/02 09:31:58 by codespace         #+#    #+#             */
/*   Updated: 2024/08/22 19:22:57 by mgardesh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_minishell_l	*ft_lstnew_lex(char *content, int type)
{
	t_minishell_l	*out;

	out = (t_minishell_l *)malloc(sizeof(*out));
	if (!out)
		return (out);
	if (!type)
		out->input = content;
	else
		out->input = NULL;
	out->str = NULL;
	out->token = type;
	out->next = NULL;
	out->prev = NULL;
	return (out);
}

t_minishell_l	*ft_lstlast_lex(t_minishell_l *lst)
{
	while (lst)
	{
		if (!lst->next)
			return (lst);
		lst = lst->next;
	}
	return (lst);
}

t_minishell_l	*ft_lstfirst_lex(t_minishell_l *lst)
{
	if (!lst)
		return (NULL);
	while (lst->prev)
	{
		lst = lst->prev;
	}
	return (lst);
}

void	ft_lstadd_back_lex(t_minishell_l **alst, t_minishell_l *new)
{
	t_minishell_l	*last;

	if (alst)
	{
		if (*alst)
		{
			last = ft_lstlast_lex(*alst);
			last->next = new;
			new->prev = last;
		}
		else
			*alst = new;
	}
}

int	check_red_type(char *str)
{
	if (!ft_strcmp(str, "|"))
		return (1);
	else if (!ft_strcmp(str, ">"))
		return (2);
	else if (!ft_strcmp(str, ">>"))
		return (3);
	else if (!ft_strcmp(str, "<"))
		return (4);
	else if (!ft_strcmp(str, "<<"))
		return (5);
	else
		return (0);
}

void	compress_lst(t_minishell_l *in)
{
	t_minishell_l	*tmp;

	while (in)
	{
		if (in->token != 0 && in->token != 1)
		{
			in->input = in->next->input;
			tmp = in->next->next;
			free(in->next);
			in->next = tmp;
			if (in->next)
				in->next->prev = in;
		}
		in = in->next;
	}
}

void	free_lex(t_minishell_l *in)
{
	t_minishell_l	*tmp;
	
	while (in)
	{
		tmp = in->next;
		free(in);
		in = tmp;	
	}
}

t_minishell_l	*lexer(t_raw_in *in)
{
	t_minishell_l	*out;
	t_minishell_l	*tmp;
	int				i;

	i = -1;
	ft_split_shell(in);
	out = NULL;
	while (++i < in->sum)
	{
		tmp = ft_lstnew_lex(in->out[i], check_red_type(in->out[i]));
		if (!tmp)
			return (free_lex(out), free_everything(NULL, NULL, in), NULL);
		ft_lstadd_back_lex(&out, tmp);
	}
	i = -1;
	tmp = out;
	while (tmp)
	{
		if (tmp->token == 5)
			tmp->str = in->del_str[++i];
		tmp = tmp->next;
	}
	compress_lst(out);
	return (out);
}
