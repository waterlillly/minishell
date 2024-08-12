/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbaumeis <lbaumeis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 18:48:06 by lbaumeis          #+#    #+#             */
/*   Updated: 2024/08/12 02:34:09 by lbaumeis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../exec.h"

int	do_echo(t_pipex *p, char **token, int x)
{
	char	*temp;

	temp = NULL;
	if (token[x][0] == '$' && token[x][1] == '?' && token[x][2] == '\0')
		return (ft_putnbr_fd(p->status, 1), 0);
	else if (token[x][0] == '$' && token[x][1] != '$' && token[x][1] != '\0'
		&& valid_env(p, ft_substr(token[x], 1, ft_strlen(token[x]) - 1)))
	{
		temp = xpand(p, token, x);
		if (!temp)
			return (1);
		return (ft_putstr_fd(temp, 1), 0);
	}
	else if (token[x][0] == '$' && token[x][1] != '\0'
		&& !valid_env(p, ft_substr(token[x], 1, ft_strlen(token[x]) - 1)))
		return (1);
	else
		return (ft_putstr_fd(token[x], 1), 0);
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

	x = 1;
	n = false;
	if (!token[x] || !ft_strcmp(token[0], "echo"))
	{
		ft_putstr_fd("\n", 1);
		return ;
	}
	if (check_n(token[x]) == true)
	{
		n = true;
		x++;
	}
	while (token[x])
	{
		if (do_echo(p, token, x) == 0)
		{
			if (token[x + 1] != NULL)
				ft_putstr_fd(" ", 1);
		}
		x++;
	}
	if (n == false)
		ft_putstr_fd("\n", 1);
}
