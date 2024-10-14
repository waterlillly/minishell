/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xpd_quotes.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbaumeis <lbaumeis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/06 17:44:11 by lbaumeis          #+#    #+#             */
/*   Updated: 2024/10/13 15:25:21 by lbaumeis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	count_q_strs(char *str, int q)
{
	int	c;
	int	x;

	c = 0;
	x = 0;
	while (str[x])
	{
		if (str[x] == q)
		{
			x++;
			while (str[x] && str[x] != q)
				x++;
			if (str[x] && str[x] == q)
			{
				x++;
				c++;
			}
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

int	q_split(char *s, int q, int pa)
{
	if (s[pa] && s[pa] == q)
	{
		pa++;
		while (s[pa] && s[pa] != q)
			pa++;
		if (s[pa] && s[pa] == q)
			pa++;
	}
	else
	{
		while (s[pa] && s[pa] != q)
			pa++;
	}
	return (pa);
}

char	**xpd_1_split(char *str, int q)
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
	y = count_q_strs(str, q);
	if (y < 1)
		return (NULL);
	s = ft_calloc(y + 1, sizeof(char *));
	if (!s)
		return (NULL);
	while (x < y)
	{
		pa = q_split(str, q, pa);
		s[x] = ft_substr(str, pb, pa - pb);
		if (!s[x])
			return (ft_free_2d(s), NULL);
		pb = pa;
		x++;
	}
	return (s);
}
