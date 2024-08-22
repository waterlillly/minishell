/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgardesh <mgardesh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/12 11:22:01 by codespace         #+#    #+#             */
/*   Updated: 2024/08/22 16:55:23 by mgardesh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_minishell_p	*ft_lstnew_parse(void)
{
	t_minishell_p	*out;

	out = (t_minishell_p *)malloc(sizeof(*out));
	if (!out)
		return (out);
	out->infile = NULL;
	out->outfile = NULL;
	out->redirect = NULL;
	out->str = NULL;
	out->std_out = 0;
	out->str_len = 0;
	out->next = NULL;
	out->prev = NULL;
	return (out);
}

t_minishell_p	*ft_lstfirst_parse(t_minishell_p *lst)
{
	if (!lst)
		return (NULL);
	while (lst->prev)
	{
		lst = lst->prev;
	}
	return (lst);
}

t_minishell_p	*ft_lstlast_parse(t_minishell_p *lst)
{
	while (lst)
	{
		if (!lst->next)
			return (lst);
		lst = lst->next;
	}
	return (lst);
}

void	ft_lstadd_back_parse(t_minishell_p **alst, t_minishell_p *new)
{
	t_minishell_p	*last;

	if (alst)
	{
		if (*alst)
		{
			last = ft_lstlast_parse(*alst);
			last->next = new;
			new->prev = last;
		}
		else
			*alst = new;
	}
}

void	clean_parse(t_minishell_p *in)
{
	int	i;
	t_minishell_l	*tmp;
	t_minishell_l	*tmp2;

	while (in)
	{
		tmp = in->redirect;
		i = 0;
		in->str = ft_calloc(in->str_len + 1, sizeof(char *));
		while (tmp)
		{
			if (tmp->token == 0)
			{
				in->str[i] = tmp->input;
				i++;
				if (tmp->prev)
					tmp->prev->next = tmp->next;
				else
					in->redirect = tmp->next;
				if (tmp->next)
					tmp->next->prev = tmp->prev;
				tmp2 = tmp->next;
				free(tmp);
				tmp = tmp2;
			}
			else
				tmp = tmp->next;
		}
		in = in->next;
	}
}

void	set_red_parse(t_minishell_p *parse, t_minishell_l *lex)
{
	t_minishell_l	*tmp;

	while (parse)
	{
		parse->redirect = lex;
		tmp = lex;
		while (tmp && tmp->token != 1)
		{
			if (tmp->token == 0)
				parse->str_len++;
			tmp = tmp->next;
		}
		if (tmp)
		{
			tmp->prev->next = NULL;
			lex = tmp->next;
			lex->prev = NULL;
			free(tmp);
		}
		parse = parse->next;
	}
}


t_minishell_p	*parser(t_minishell_l *in, t_raw_in *raw)
{
	t_minishell_p	*out;
	t_minishell_p	*tmp;
	int				i;

	i = -1;
	out = NULL;
	while (++i < raw->n_pipe + 1)
	{
		tmp = ft_lstnew_parse();
		ft_lstadd_back_parse(&out, tmp);
	}
	set_red_parse(out, in);
	clean_parse(out);
	//set_parse(out);
	return (out);
}
