/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/01 18:17:03 by lbaumeis          #+#    #+#             */
/*   Updated: 2023/10/14 15:06:10 by lbaumeis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_countstrs(char const *s, char c)
{
	int	counter;

	counter = 0;
	if (!s)
		return (0);
	while (*s)
	{
		while (*s == c && *s)
			s++;
		if (*s)
			counter++;
		while (*s != c && *s)
			s++;
	}
	return (counter);
}

static int	ft_place(char const *s, char c, int last_pos)
{
	while (s[last_pos] != '\0' && s[last_pos] != c)
		last_pos++;
	return (last_pos);
}

char	**ft_split(char const *s, char c)
{
	char	**result;
	int		x;
	int		last_pos;

	last_pos = 0;
	result = malloc((ft_countstrs(s, c) + 1) * sizeof(char *));
	if (!s || !result)
		return (NULL);
	x = 0;
	while (x < ft_countstrs(s, c))
	{
		while (s[last_pos] == c)
			last_pos++;
		result[x] = ft_substr(s, last_pos, ft_place(s, c, last_pos) - last_pos);
		if (!result[x++])
		{
			while (x > 0)
				free(result[--x]);
			free(result);
			return (NULL);
		}
		last_pos = ft_place(s, c, last_pos + 1);
	}
	result[x] = NULL;
	return (result);
}
/*
int main(void)
{
    char const 	*s = "1  22   333    4444     55555                 ";
    char       	c = ' ';
    char       	**split = ft_split(s, c);
    int        	i = 0;
	
	while (i <= ft_countstrs(s, c))
    {
        printf("[%s]\n", split[i]);
        i++;
    }
	if (!split)
		{
			while (split && i >= 0)
				free(split[i--]);
			free(split);
		}
	// ft_free(split, (i+1));
    return (0);
}
*/
