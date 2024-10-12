/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbaumeis <lbaumeis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 18:48:06 by lbaumeis          #+#    #+#             */
/*   Updated: 2024/10/12 18:45:45 by lbaumeis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*split_and_xpand(t_pipex *p, char **s)
{
	char	*temp;
	char	*str;
	int		y;

	y = 0;
	str = NULL;
	temp = NULL;
	if (!s || !p)
		return (NULL);
	while (s[y])
	{
		temp = xpand(p, s, y);
		if (temp)
		{
			str = ft_strjoin_free_both(str, temp);
			if (!str)
				return (NULL);
		}
		y++;
	}
	return (str);
}

int	dollar_count(char *s)
{
	int	x;
	int	y;

	x = 0;
	y = 0;
	if (!s)
		return (0);
	while (s[x])
	{
		if (s[x] == '$')
			y++;
		x++;
	}
	return (y);
}

bool	even_q(char *s)
{
	int	x;
	int	y;

	x = 0;
	y = 0;
	if (!s)
		return (false);
	while (s[x++] && s[x] == '\"')
		y++;
	if (y > 0 && y % 2 != 0)
		return (true);
	return (false);
}

int	do_echo(char **token, int x, int start)
{
	if (!token || !token[x] || (x == start && ft_strcmp_bool(token[x], "echo"))
		|| (x == start + 1 && ft_strcmp_bool(token[x - 1], "echo") && check_n(token[x]))
		|| (x > start + 1 && check_n(token[x - 1]) && check_n(token[x])))
		return (1);
	return (ft_putstr_fd(token[x], 1), 0);
}

bool	check_n(char *token)
{
	int		x;
	bool	n;

	n = true;
	if (!token)
		return (false);
	x = 0;
	while (n)
	{
		if (token[x] && x == 0 && token[x] == '-')
			x++;
		else if (token[x] && x >= 1 && token[x] == 'n')
			x++;
		else if (x >= 2)
		{
			if (token[x] && token[x] == 'n')
				x++;
			if (!token[x])
				break ;
			else
				n = false;
		}
		else
			n = false;
	}
	return (n);
}

int	echo(char **token)
{
	int	x;
	int	y;
	int	start;

	x = 0;
	y = 0;
	if (!token)
		return (1);
	while (token[x] && ft_strlen(token[x]) == 0)
		x++;
	if (!token[x] || !ft_strcmp_bool(token[x], "echo"))
		return (1);
	start = x;
	if (!token[x + 1])
		return (ft_putstr_fd("\n", 1), 0);
	while (token[x])
	{
		y = do_echo(token, x, start);
		if (y != 1 && token[x] && token[x + 1])
			ft_putstr_fd(" ", 1);
		x++;
	}
	if (check_n(token[start + 1]))
		return (0);
	return (ft_putstr_fd("\n", 1), 0);
}
