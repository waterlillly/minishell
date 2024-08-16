/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgardesh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/06 11:32:36 by mgardesh          #+#    #+#             */
/*   Updated: 2023/09/06 11:47:27 by mgardesh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*ft_strcpy(char *dest, char *src)
{
	int	i;

	i = 0;
	while (src[i] != '\0')
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

char	*ft_strdup(const char *s)
{
	char	*s2;
	char	*src;
	int		i;

	i = 0;
	src = (char *)s;
	while (src[i])
		i++;
	s2 = (char *)malloc((i + 1) * sizeof(char));
	if (s2 == NULL)
		return (NULL);
	return (ft_strcpy(s2, src));
}
