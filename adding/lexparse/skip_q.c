/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   skip_q.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 11:19:13 by codespace         #+#    #+#             */
/*   Updated: 2024/08/08 11:20:00 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*skip_q(char *str)
{
	if (*str == '\"')
	{
		str++;
		while (*str != '\"')
			str++;
	}
	else if (*str == '\'')
	{
		str++;
		while (*str != '\'')
			str++;
	}
	return (str);
}