/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbaumeis <lbaumeis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/27 13:48:57 by lbaumeis          #+#    #+#             */
/*   Updated: 2024/10/03 14:59:51 by lbaumeis         ###   ########.fr       */
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
	if (!str || !tok || !str[x])
		return (-1);
	while (str[x] && tok)
	{
		y = 0;
		while (tok[y] && str[x][y] && tok[y] == str[x][y])
		{
			y++;
			if (tok[y] == '\0' && (str[x][y] == '\0' || str[x][y] == '='))
				return (x);
		}
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
	ret = (char *)ft_calloc((c + 1), sizeof(char));
	if (!ret)
		return (NULL);
	while (x < c && v_part[x])
	{
		ret[x] = v_part[x];
		x++;
	}
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

char	**update_free_arr(char **old, char **new)
{
	int		x;
	char	**ret;

	x = 0;
	ret = NULL;
	if (!old || !new)
		return (NULL);
	ft_free_2d(old);
	ret = ft_calloc((ft_arrlen(new) + 1), sizeof(char *));
	if (!ret)
		return (ft_free_2d(new), NULL);
	while (new[x])
	{
		ret[x] = ft_strdup(new[x]);
		if (!ret[x])
			return (ft_free_2d(new), ft_free_2d(ret), NULL);
		x++;
	}
	ret[x] = NULL;
	if (new)
		ft_free_2d(new);
	return (ret);
}

int	ft_strsrc(char *s, int c)
{
	int	i;

	i = 0;
	if (!s)
		return (-1);
	while (s[i])
	{
		if (s[i] == c)
			return (i);
		i++;
	}
	return (-1);
}
