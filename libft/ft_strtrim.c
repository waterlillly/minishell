/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbaumeis <lbaumeis@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 18:16:47 by lbaumeis          #+#    #+#             */
/*   Updated: 2024/08/14 15:52:01 by lbaumeis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	i;
	size_t	start;
	size_t	len;
	char	*new;

	i = 0;
	if (!s1)
		return (NULL);
	if (!set)
		return ((char *)s1);
	len = ft_strlen(s1) - 1;
	while (s1 && ft_strchr(set, s1[i]))
		i++;
	if (!(ft_strchr(set, s1[i])))
		start = i;
	while (s1 && ft_strrchr(set, s1[len]))
		len--;
	if (!(ft_strrchr(set, s1[len])))
	{
		new = ft_substr(s1, start, (len - i + 1));
		if (!new)
			return (NULL);
		return (new);
	}
	return (NULL);
}

/*
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
*/