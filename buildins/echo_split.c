/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_split.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbaumeis <lbaumeis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/31 17:54:22 by lbaumeis          #+#    #+#             */
/*   Updated: 2024/09/13 14:38:42 by lbaumeis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	countstrs(char *s, char c)
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

int	do_split(char *s, char c, int pos_a)
{
	if (s[pos_a] && s[pos_a] == c)
	{
		pos_a++;
		if (s[pos_a] && s[pos_a] == c)
			pos_a++;
		else
		{
			while (s[pos_a] && s[pos_a] != c)
				pos_a++;
		}
	}
	else
	{
		while (s[pos_a] && s[pos_a] != c)
		pos_a++;
	}
	return (pos_a);
}

char	**echo_split(char *s, int c)
{
	int		pos_a;
	int		pos_b;
	int		x;
	char	**result;

	pos_a = 0;
	pos_b = 0;
	x = 0;
	result = NULL;
	if (!s || countstrs(s, c) < 1)
		return (NULL);
	result = ft_calloc(countstrs(s, c) + 1, sizeof(char *));
	if (!result)
		return (NULL);
	while (x < countstrs(s, c))
	{
		pos_a = do_split(s, c, pos_a);
		result[x] = ft_substr(s, pos_b, pos_a - pos_b);
		if (!result[x])
			return (ft_free_double(result), NULL);
		pos_b = pos_a;
		x++;
	}
	return (result);
}
