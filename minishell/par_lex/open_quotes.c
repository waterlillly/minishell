/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_quotes.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbaumeis <lbaumeis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 17:56:37 by codespace         #+#    #+#             */
/*   Updated: 2024/08/06 19:17:37 by lbaumeis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int open_quotes(char *input)
{
	int	single_q;
	int	double_q;

	single_q = single_count(input);
	double_q = double_count(input);
	if (single_q % 2 || double_q % 2)
		return (0);
	return (1);
}