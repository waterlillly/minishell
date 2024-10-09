/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xpd_space.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbaumeis <lbaumeis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/06 17:41:53 by lbaumeis          #+#    #+#             */
/*   Updated: 2024/10/06 18:06:46 by lbaumeis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	count_space_strs(char *str, int q)
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
			while (str[x] && str[x] == q)
				x++;
			if (str[x] && str[x] != q)
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

int	space_split(char *s, int d, int pa)
{
	if (s[pa] && s[pa] == d)
	{
		pa++;
		while (s[pa] && s[pa] == d)
			pa++;
	}
	else
	{
		while (s[pa] && s[pa] != d)
			pa++;
	}
	return (pa);
}

char	**xpd_3_split(char *str, int q)
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
	y = count_space_strs(str, q);
	if (y < 1)
		return (NULL);
	s = ft_calloc(y + 1, sizeof(char *));
	if (!s)
		return (NULL);
	while (x < y)
	{
		pa = space_split(str, q, pa);
		s[x] = ft_substr(str, pb, pa - pb);
		pb = pa;
		x++;
	}
	free(str);
	return (s);
}

char	**d_q_space(char **s)
{
	char	**arr;
	char	**tmp;
	int		i;
	
	i = 0;
	arr = NULL;
	while (s[i])
	{
		if (d_out_q(s[i]) && ft_strchr(s[i], '$') && ft_strchr(s[i], ' '))
			tmp = xpd_3_split(rm_out_q(s[i]), ' ');
		else
		{
			tmp = ft_calloc(2, sizeof(char *));
			if (!tmp)
				return (NULL);
			*tmp = ft_strdup(s[i]);
		}
		arr = arrjoin(arr, tmp);
		i++;
	}
	ft_free_2d(s);
	return (arr);
}
