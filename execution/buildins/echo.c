/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbaumeis <lbaumeis@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 18:48:06 by lbaumeis          #+#    #+#             */
/*   Updated: 2024/08/01 19:32:42 by lbaumeis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "buildins.h"

char	*expand(t_buildins *vars, char **token, int x)
{
	char	*temp;

	temp = NULL;
	temp = get_env(vars, ft_substr(token[x], 1, ft_strlen(token[x] - 1)));
	if (!temp)
		err_or("substr");
	return (temp);
}

void	echo(t_buildins *vars, char **token)
{
	char	*temp;
	int		x;

	x = 0;
	temp = NULL;
	x = find_arg(token, "echo") + 1;
	while (token[x])
	{
		if (token[x][0] == '$')
		{
			temp = expand(vars, token, x);
			if (!temp)
				err_or("strjoin space1");
			printf("%s", temp);
			free(temp);
			temp = NULL;
		}
		else
			printf("%s", token[x]);
		x++;
		if (token[x] != NULL)
			printf(" ");
	}
	printf("\n");
}
