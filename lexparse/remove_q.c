/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_q.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbaumeis <lbaumeis@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 17:52:56 by codespace         #+#    #+#             */
/*   Updated: 2024/08/14 14:37:29 by lbaumeis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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