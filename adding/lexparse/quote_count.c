/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_count.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbaumeis <lbaumeis@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 17:54:26 by codespace         #+#    #+#             */
/*   Updated: 2024/08/14 14:37:25 by lbaumeis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	double_count(char *input)
{
	int	i;
	int	single_q;

	i = 0;
	single_q = 0;
	while (*input)
	{
		if (*input == '\'' && i % 2 == 0)
			single_q++;
		if (*input == '\"' && single_q % 2 == 0)
			i++;
		input++;
	}
	return (i);
}

int	single_count(char *input)
{
	int	i;
	int	double_q;

	i = 0;
	double_q = 0;
	while (*input)
	{
		if (*input == '\"' && i % 2 == 0)
			double_q++;
		if (*input == '\'' && double_q % 2 == 0)
			i++;
		input++;
	}
	return (i);
}