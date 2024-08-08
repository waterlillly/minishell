/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_syntax.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 11:11:56 by codespace         #+#    #+#             */
/*   Updated: 2024/08/08 11:18:49 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	is_invalid(char c)
{
	if (c == '>' || c == '<' || c == '|' || c == '\n' || c == 0)
		return (1);
	return (0);
}

int	check_red(char *str)
{
	int	i;

	while (*str)
	{
		i = 1;
		str = skip_q(str);
		if (*str == '<')
		{
			if (*(str + i) == '<')
				i++;
			while (is_sep(" \t", *(str + i)))
				i++;
			if (is_invalid(*(str + i)))
				return (0);
			str = str + i - 1;
		}
		if (*str == '>')
		{
			if (*(str + i) == '>')
				i++;
			while (is_sep(" \t", *(str + i)))
				i++;
			if (is_invalid(*(str + i)))
				return (0);
			str = str + i - 1;
		}
		str++;
	}
	return (1);
}

int	check_spipe(char *str)
{
	while (is_sep(" \t", *str))
		str++;
	if (*str == '|')
		return (1);
	return (0);
}

int	check_pipe(char *str)
{
	int 	i;

	if (check_spipe(str))
		return (0);
	while (*str)
	{
		i = 1;
		str = skip_q(str);
		if (*str == ';')
			return (0);
		if (*str == '|')
		{
			while (is_sep(" \t", *(str + i)))
				i++;
			if (*(str + i) == '|')
				return (0);
			str = str + i - 1;
		}
		str++;
	}
	return (1);
}

int	check_syntax(char *input)
{
	if (!open_quotes(input) || !check_red(input) || !check_pipe(input))
		return (0);
	return (1);
}