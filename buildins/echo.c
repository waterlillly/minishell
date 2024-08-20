/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbaumeis <lbaumeis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 18:48:06 by lbaumeis          #+#    #+#             */
/*   Updated: 2024/08/20 18:33:55 by lbaumeis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	do_echo(t_pipex *p, char **token, int x)
{
	if (check_n(token[x]))
		return (0);
	if (token[x][0] == '$' && token[x][1] == '?' && token[x][2] == '\0')
		return (ft_putnbr_fd(p->status, 1), 0);
	else
	{
		if (xpand(p, token, x) == NULL)
			return (1);
		return (ft_putstr_fd(xpand(p, token, x), 1), 0);
	}
}

bool	check_n(char *token)
{
	int	x;

	x = 2;
	if (token[0] == '-' && token[1] == 'n')
	{
		if (token[x] == '\0')
			return (true);
		while (token[x] == 'n')
			x++;
		if (token[x] == '\0')
			return (true);
	}
	return (false);
}

int	echo(t_pipex *p, char **token)
{
	int	x;
	int	y;

	y = 0;
	if (!p || !token || !ft_strcmp_bool(token[0], "echo"))
		return (1);
	if (!token[1])
	{
		ft_putstr_fd("\n", 1);
		return (0);
	}
	x = 0;
	while (token[++x])
	{
		y = do_echo(p, token, x);
		if (y != 1 && token[x + 1])
			ft_putstr_fd(" ", 1);
	}
	if (check_n(token[1]) == false)
		ft_putstr_fd("\n", 1);
	return (0);
}
