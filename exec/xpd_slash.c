/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xpd_slash.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbaumeis <lbaumeis@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 15:06:35 by lbaumeis          #+#    #+#             */
/*   Updated: 2024/10/15 21:43:12 by lbaumeis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	count_slash_strs(char *str, int q)
{
	int	c;
	int	x;

	c = 0;
	x = 0;
	while (str[x])
	{
		if (str[x] == q)
		{
			c++;
			x++;
			while (str[x] && str[x] != q)
				x++;
		}
		else
		{
			while (str[x] && str[x] != q)
				x++;
			c++;
		}
	}
	return (c);
}

int	slash_split(char *s, int q, int pa)
{
	if (s[pa] && s[pa] == q)
	{
		pa++;
		while (s[pa] && s[pa] != q)
			pa++;
	}
	else
	{
		while (s[pa] && s[pa] != q)
			pa++;
	}
	return (pa);
}

char	**xpd_slash_split(char *str, int q)
{
	int		pa;
	int		pb;
	int		x;
	int		y;
	char	**s;

	x = 0;
	pa = 0;
	pb = 0;
	if (!str)
		return (NULL);
	y = count_slash_strs(str, q);
	if (y < 1)
		return (NULL);
	s = ft_calloc(y + 1, sizeof(char *));
	if (!s)
		return (NULL);
	while (x < y)
	{
		pa = slash_split(str, q, pa);
		s[x] = ft_substr(str, pb, pa - pb);
		if (!s[x])
			return (ft_free_2d(s), NULL);
		pb = pa;
		x++;
	}
	return (s);
}
