/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbaumeis <lbaumeis@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 18:16:47 by lbaumeis          #+#    #+#             */
/*   Updated: 2024/06/25 14:56:03 by lbaumeis         ###   ########.fr       */
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
