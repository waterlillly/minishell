/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbaumeis <lbaumeis@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/27 13:48:57 by lbaumeis          #+#    #+#             */
/*   Updated: 2024/08/18 16:52:28 by lbaumeis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

bool	is_access(char *dir)
{
	if ((access(dir, F_OK) == 0))
		return (true);
	return (false);
}

int	find_arg(char **s, char *a)
{
	int	x;

	x = 0;
	if (!s || !a)
		return (-1);
	while (s[x])
	{
		if (ft_strcmp_bool(s[x], a))
			return (x);
		x++;
	}
	return (-1);
}

int	find_str_part(char **str, char *tok)
{
	int	x;
	int	y;

	x = 0;
	if (!str || !tok)
		return (-1);
	while (str[x] && tok)
	{
		y = 0;
		while (tok[y] && str[x][y] && tok[y] == str[x][y])
			y++;
		if (tok[y] == '\0' && (str[x][y] == '=' || str[x][y] == '\0'))
			return (x);
		x++;
	}
	return (-1);
}

char	*strcpy_until(char *v_part)
{
	char	*ret;
	int		c;
	int		x;

	c = 0;
	x = 0;
	if (!v_part)
		return (NULL);
	while (v_part[c] && v_part[c] != '=')
		c++;
	ret = NULL;
	ret = malloc(sizeof(char) * (c + 1));
	if (!ret)
		return (NULL);
	while (x < c && v_part[x])
	{
		ret[x] = v_part[x];
		x++;
	}
	ret[x] = '\0';
	return (ret);
}

int	ft_strcmp_until(const char *s1, const char *s2)
{
	int	x;

	x = 0;
	if (!s1 || !s2)
		return (0);
	while (s1[x] && s2[x] && s1[x] == s2[x] && s1[x] != '=' && s2[x] != '=')
		x++;
	if (s1[x] == '=' && s2[x] == '=')
		return (0);
	else
		return (s2[x] - s1[x]);
}
