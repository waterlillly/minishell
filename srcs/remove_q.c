/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_q.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 17:52:56 by codespace         #+#    #+#             */
/*   Updated: 2024/07/29 18:54:18 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	remove_q(t_raw_in *in)
{
	int		i;
	char	*tmp;

	i = -1;
	while (++i < in->n_hd)
	{
		if (*in->del_s[i] == '\'' || *in->del_s[i] == '\"')
		{
			tmp = ft_substr(in->del_s[i], 1, ft_strlen(in->del_s[i]) - 2);
			free(in->del_s[i]);
			in->del_s[i] = tmp;
		}
	}
}