/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbaumeis <lbaumeis@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 13:00:22 by lbaumeis          #+#    #+#             */
/*   Updated: 2024/08/01 19:13:52 by lbaumeis         ###   ########.fr       */
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

int	fill_and_expand(t_buildins *vars, char **token, char **new_token, int y)
{
	char	*exs;
	int		x;

	exs = NULL;
	x = find_dollar(token, y);
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
	return (y + 1);
}

char	*check_expand(char **new_token)
{
	int		x;
	int		y;
	char	*tok;

	x = 0;
	tok = NULL;
	y = how_many(new_token, "\n");
	if (y == ft_arrlen(new_token) - 1)
		tok = ft_strdup("\n");
	else
	{
		while (new_token[x])
		{
			if (!ft_strcmp(new_token[x], "\n"))
			{
				tok = ft_strjoin_space_free(tok, new_token[x]);
				if (!tok)
					err_or("strjoin");
			}
			x++;
		}
	}
	ft_free_double(new_token);
	return (tok);
}

char	*token_expand(t_buildins *vars, char **tok)
{
	int		dollars;
	int		y;
	char	**new_token;

	y = 0;
	dollars = 0;
	new_token = NULL;
	new_token = malloc(sizeof(char *) * (ft_arrlen(token) + 1));
	if (!new_token)
		err_or("malloc");
	dollars = find_dollars(token);
	while (dollars > 0)
	{
		y = fill_and_expand(vars, token, new_token, y);
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
	return (check_expand(new_token));
}

char	**cleanup(char **token, int x, char **tok)
{
	tok = malloc(sizeof(char *) * (ft_arrlen(token) - x));
	if (!tok)
		err_or("malloc");
	x++;
	while (token[x])
	{
		*tok = ft_strdup(token[x]);
		if (!*tok)
			err_or("strdup");
		x++;
		tok++;
	}
	*tok = NULL;
	return (tok);
}

void	echo(t_buildins *vars, char **token)
{
	int		x;
	char	**tok;
	char	*s;

	x = 0;
	tok = NULL;
	s = NULL;
	x = find_arg(token, "echo");
	if (x >= 0)
	{
		tok = cleanup(token, x, tok);
		if (!tok)
			err_or("cleanup");
	}
	s = token_expand(vars, tok) ;
	ft_free_double(tok);
	if (!s)
		err_or("check_expand");
	ft_putendl_fd(s, 1);
	free(s);
	s = NULL;
}
