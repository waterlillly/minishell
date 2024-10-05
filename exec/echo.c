/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbaumeis <lbaumeis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 18:48:06 by lbaumeis          #+#    #+#             */
/*   Updated: 2024/10/05 20:07:02 by lbaumeis         ###   ########.fr       */
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

int	do_echo(char **token, int x)
{
	if (!token || !token[x]
		|| (x == 1 && ft_strcmp_bool(token[0], "echo") && check_n(token[x])))
		return (1);
	else if ((!check_s_q(token[x]) && only_dollars(rm_q(token[x])))
		|| only_dollars(token[x]))
	{
		if (even_q(token[x]) && dollar_count(token[x]) == 1)
			return (0);
		else
			return (ft_putstr_fd(rm_q(token[x]), 1), 0);
	}
	return (ft_putstr_fd(token[x], 1), 0);
}

bool	check_n(char *token)
{
	int		x;
	bool	n;

	x = 0;
	n = true;
	if (!token)
		return (false);
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

	y = 0;
	if (!token || !token[0])
		return (1);
	if (!token[1])
		return (ft_putstr_fd("\n", 1), 0);
	x = 1;
	while (token[x])
	{
		y = do_echo(token, x);
		if (y != 1 && ft_strlen(token[x]) > 0 && token[x + 1])
			ft_putstr_fd(" ", 1);
		x++;
	}
	if (check_n(token[1]))
		return (0);
	return (ft_putstr_fd("\n", 1), 0);
}
