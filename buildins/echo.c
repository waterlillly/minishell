/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgardesh <mgardesh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 18:48:06 by lbaumeis          #+#    #+#             */
/*   Updated: 2024/09/16 17:39:27 by mgardesh         ###   ########.fr       */
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
	while (s[x++])
	{
		if (s[x] == '$')
			y++;
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

int	do_echo(t_pipex *p, char **token, int x)
{
	char	*str;
	char	**s;
	
	str = NULL;
	s = NULL;
	if (!token || !token[x]
		|| (x == 1 && ft_strcmp_bool(token[0], "echo") && check_n(token[x])))
		return (1);
	if (ft_strcmp_bool(token[1], "$?"))
		return (ft_putnbr_fd((int)p->status, 1), 0);
	if ((!check_s_q(token[x]) && only_dollars(rm_q(token[x]))) || only_dollars(token[x]))
	{
		if (even_q(token[x]) && dollar_count(token[x]) == 1)
			return (0);
		else
			str = rm_q(token[x]);
	}
	else if (!s_out_q(token[x]))
		s = echo_split(token[x], '$');
	if (!str)
	{
		if (s)
			str = split_and_xpand(p, s);
		else
			str = xpand(p, token, x);
		if (!str)
			return (ft_free_double(s), 1);
	}
	ft_putstr_fd(str, 1);
	return (ft_free_double(s), free(str), str = NULL, 0);
}

bool	check_n(char *token)
{
	int	x;

	x = 0;
	if (!token)
		return (false);
	while (token[x])
	{
		if (x == 0 && token[x] && token[x] == '-')
			x++;
		else if (x >= 1 && token[x] && token[x] == 'n')
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
	x = 1;
	while (token[x])
	{
		y = do_echo(p, token, x);
		if (y != 1 && token[x + 1])
			ft_putstr_fd(" ", 1);
		x++;
	}
	if (check_n(token[1]))
		return (0);
	return (ft_putstr_fd("\n", 1), 0);
}
