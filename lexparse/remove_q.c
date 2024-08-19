/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_q.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 17:52:56 by codespace         #+#    #+#             */
/*   Updated: 2024/08/18 17:12:51 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	move_e(char *str)
{
	char	tmp;

	while (*(str + 1))
	{
		tmp = *(str + 1);
		*(str + 1) = *str;
		*str = tmp;
		str++;
	}
	*str = '\0';
}

void	remove_q(char **in, int len)
{
	int		i;
	int		j;
	int		change;
	int		dq;
	int		sq;

	i = -1;
	while (++i < len)
	{
		j = 0;
		sq = 0;
		dq = 0;
		change = 0;
		while(in[i][j])
		{
			if (change != is_oq(in[i][j], &dq, &sq))
			{
				if (change)
					change = 0;
				else
					change = 1;
				move_e(&in[i][j]);
			}
			else
				j++;
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