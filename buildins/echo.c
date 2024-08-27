/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbaumeis <lbaumeis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 18:48:06 by lbaumeis          #+#    #+#             */
/*   Updated: 2024/08/25 14:27:47 by lbaumeis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	do_echo(t_pipex *p, char **token, int x)
{
	char	*str;

	if (!token || !token[x])
		return (1);
	if (x == 1 && ft_strcmp_bool(token[0], "echo") && check_n(token[x]))
		return (1);
	if (token[x][0] == '$' && token[x][1] == '?' && token[x][2] == '\0')
		return (ft_putnbr_fd(p->status, 1), 0);
	else
	{
		str = xpand(p, token, x);
		if (!str)
			return (1);
		ft_putstr_fd(str, 1);
		return (0);
	}
}

bool	check_n(char *token)
{
	int	x;

	x = 0;
	if (!token)
		return (false);
	while (token[x])
	{
		if (x == 0 && token[x] == '-')
			x++;
		else if (x >= 1 && token[x] == 'n')
			x++;
		else if (x >= 2 && token[x] == '\0')
			return (true);
		else
			return (false);
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
		return (ft_putstr_fd("\n", 1), 0);
	x = 0;
	while (token[++x])
	{
		y = do_echo(p, token, x);
		if (y != 1 && token[x + 1])
			ft_putstr_fd(" ", 1);
	}
	if (check_n(token[1]))
		return (0);
	return (ft_putstr_fd("\n", 1), 0);
}
