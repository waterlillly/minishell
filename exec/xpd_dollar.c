/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xpd_dollar.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbaumeis <lbaumeis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/06 17:48:26 by lbaumeis          #+#    #+#             */
/*   Updated: 2024/10/06 19:28:52 by lbaumeis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	count_dlr_strs(char *s, char c)
{
	int	counter;
	int	x;

	counter = 0;
	x = 0;
	while (s[x])
	{
		if (s[x] == c)
		{
			x++;
			if (s[x] == c || s[x] == '\0')
			{
				x++;
				counter++;
			}
		}
		else
		{
			while (s[x] && s[x] != c)
				x++;
			counter++;
		}
	}
	return (counter);
}

int	dlr_split(char *s, int d, int pa)
{
	if (s[pa] && s[pa] == d)
	{
		pa++;
		if (s[pa] && s[pa] == d)
			pa++;
		else
		{
			while (s[pa] && s[pa] != d)
				pa++;
		}
	}
	else
	{
		while (s[pa] && s[pa] != d)
			pa++;
	}
	return (pa);
}

char	**xpd_2_split(char *str, int q)
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
	y = count_dlr_strs(str, q);
	if (y < 1)
		return (NULL);
	s = ft_calloc(y + 1, sizeof(char *));
	if (!s)
		return (NULL);
	while (x < y)
	{
		pa = dlr_split(str, q, pa);
		s[x] = ft_substr(str, pb, pa - pb);
		pb = pa;
		x++;
	}
	return (s);
}
