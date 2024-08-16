/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgardesh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/06 16:03:03 by mgardesh          #+#    #+#             */
/*   Updated: 2023/09/06 16:27:52 by mgardesh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	find_start(char const *s1, char const *set)
{
	size_t	find;
	size_t	i;

	find = 0;
	i = -1;
	while (s1[find])
	{
		while (set[++i])
		{
			if (set[i] == s1[find])
			{
				find++;
				i = -1;
				continue ;
			}
		}
		if (i == ft_strlen(set))
			return (find);
	}
	return (find);
}

static int	find_end(char const *s1, char const *set)
{
	int		find;
	size_t	i;

	find = ft_strlen(s1) - 1;
	i = -1;
	while (find >= 0)
	{
		while (set[++i])
		{
			if (set[i] == s1[find])
			{
				find--;
				if (find == -1)
					return (find);
				i = -1;
				continue ;
			}
		}
		if (i == ft_strlen(set))
			return (find);
	}
	return (find);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	start;
	int		end;

	if (!s1 || !set)
		return ((char *)s1);
	start = find_start(s1, set);
	end = find_end(s1, set);
	if (end < (int)start)
		return (ft_substr(s1, end + 1, 0));
	else
		return (ft_substr(s1, start, end - start + 1));
}
