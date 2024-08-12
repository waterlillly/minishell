/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_q.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 17:52:56 by codespace         #+#    #+#             */
/*   Updated: 2024/08/09 12:34:31 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	remove_dq(char **in, int len)
{
	int		i;
	char	*tmp;

	i = -1;
	while (++i < len)
	{
		if (*in[i] == '\"')
		{
			tmp = ft_substr(in[i], 1, ft_strlen(in[i]) - 2);
			free(in[i]);
			in[i] = tmp;
		}
	}
}

void	remove_sq(char **in, int len)
{
	int		i;
	char	*tmp;

	i = -1;
	while (++i < len)
	{
		if (*in[i] == '\'')
		{
			tmp = ft_substr(in[i], 1, ft_strlen(in[i]) - 2);
			free(in[i]);
			in[i] = tmp;
		}
	}
}