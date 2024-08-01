/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbaumeis <lbaumeis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 13:00:22 by lbaumeis          #+#    #+#             */
/*   Updated: 2024/08/01 15:51:57 by lbaumeis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "buildins.h"

int	find_dollars(char **token)
{
	int	x;
	int	y;

	x = 0;
	y = 0;
	while (token[x])
	{
		if (token[x][0] == '$')
			y++;
		x++;
	}
	return (y);
}

int	find_dollar(char **token, int x)
{
	while (token[x])
	{
		if (token[x][0] == '$')
			return (x);
		x++;
	}
	return (-1);
}

char	*expand(t_buildins *vars, char **token, int x)
{
	char	*s;
	char	*temp;

	s = NULL;
	temp = NULL;
	temp = ft_substr(token[x], 1, ft_strlen(token[x]) - 1);
	if (!temp)
		err_or("substr failed");
	s = get_env(vars, temp);
	free(temp);
	temp = NULL;
	if (!s)
		return (NULL);
	return (s);
}

int	fill_and_expand(t_buildins *vars, char **token, int x, char **new_token, int y)
{
	char	*exs;
	int		x;

	exs = NULL;
	x = find_dollar(token, x + 1);
	if (x < 0)
		return (y);
	while (token[y] && y < x)
	{
		new_token[y] = ft_strdup(token[y]);
		if (!new_token[y])
			err_or("strdup");
		y++;
	}
	exs = expand(vars, token, x);
	if (!exs)
		err_or("expand");
	new_token[y] = ft_strdup(exs);
	free(exs);
	exs = NULL;
	if (!new_token[y])
		err_or("strdup");
	y++;
	return (y);
}

char	**check_expand(t_buildins *vars, char **token)
{
	int		dollars;
	int		x;
	int		y;
	char	**new_token;

	x = 0;
	y = 0;
	dollars = 0;
	new_token = NULL;
	new_token = malloc(sizeof(char *) * (ft_arrlen(token) + 1));
	if (!new_token)
		err_or("malloc");
	dollars = find_dollars(token);
	if (dollars < 1)
		return (token);
	x = find_dollar(token, 0);
	while (token[y] && y < x)
	{
		new_token[y] = ft_strdup(token[y]);
		if (!new_token[y])
			err_or("strdup");
		y++;
	}
	while (dollars > 0)
	{
		y = fill_and_expand(vars, x, token, new_token, y);
		dollars--;
	}
	while (token[y])
	{
		new_token[y] = ft_strdup(token[y]);
		if (!new_token[y])
			err_or("strdup");
		y++;
	}
	new_token[y] = NULL;
	return (new_token);
}

void	echo(t_buildins *vars, char **token)
{
	int		x;
	int		y;
	char	*s;
	char	*temp;

	x = 0;
	y = 0;
	s = NULL;
	temp = NULL;
	x = find_arg(token, "echo");
	if (x >= 0)
	{
		x++;
		validate_dollars(vars, token);
		while (token[x])
		{
			if (token[x][0] == '$')
			{
				temp = expand(vars, token, x, temp);
				if (!temp)
					err_or("expand");
				if (ft_strcmp(temp, "\n") && find_dollars(token) > 1)
					validate_dollars(vars, token);///
				else
					s = ft_strjoin_free_both(s, temp);
				if (!s)
					err_or("strjoin failed");
			}
			else
			{
				s = ft_strjoin_free_one(s, token[x]);
				if (!s)
					err_or("strjoin failed");
			}
			x++;
		}
		ft_putendl_fd(s, 1);
		free(s);
		s = NULL;
	}
}
