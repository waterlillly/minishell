/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbaumeis <lbaumeis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 18:48:06 by lbaumeis          #+#    #+#             */
/*   Updated: 2024/08/07 17:11:02 by lbaumeis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../exec.h"

void	do_echo(t_pipex *p, char **token, int x)
{
	if (token[x][0] == '\'')
		ft_putstr_fd(token[x], 1);
	else if (token[x][0] == '$' && token[x][1] != '$' && token[x][1] != '\0')
		ft_putstr_fd(xpand(p, token, x), 1);
	else
		ft_putstr_fd(token[x], 1);
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

void	echo(t_pipex *p, char **token)
{
	bool	n;
	int		x;

	x = 0;
	n = false;
	x = find_arg(token, "echo") + 1;
	if (check_n(token[x]) == true)
	{
		n = true;
		x++;
	}
	while (token[x])
	{
		do_echo(p, token, x);
		x++;
		if (token[x] != NULL)
			ft_putstr_fd(" ", 1);
	}
	if (n == false)
		ft_putstr_fd("\n", 1);
}
