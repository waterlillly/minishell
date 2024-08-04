/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbaumeis <lbaumeis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 18:48:06 by lbaumeis          #+#    #+#             */
/*   Updated: 2024/08/04 16:24:30 by lbaumeis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "buildins.h"

void	do_echo(t_buildins *vars, char **token, int x, char *temp)
{
	if (token[x][0] == '$' && token[x][1] != '$' && token[x][1] != '\0')
	{
		temp = expand(vars, token, x);
		if (!temp)
			err_or("strjoin space");
		ft_putstr_fd(temp, 1);
		free(temp);
		temp = NULL;
	}
	else
		ft_putstr_fd(token[x], 1);
}

void	echo(t_buildins *vars, char **token)
{
	char	*temp;
	bool	n;
	int		x;

	x = 0;
	n = false;
	temp = NULL;
	x = find_arg(token, "echo") + 1;
	if (ft_strcmp(token[x], "-n"))
	{
		n = true;
		x++;
	}
	while (token[x])
	{
		do_echo(vars, token, x, temp);
		x++;
		if (token[x] != NULL)
			ft_putstr_fd(" ", 1);
	}
	if (n == false)
		ft_putstr_fd("\n", 1);
}
