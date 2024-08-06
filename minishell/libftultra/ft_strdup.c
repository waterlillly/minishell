/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbaumeis <lbaumeis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 16:40:01 by lbaumeis          #+#    #+#             */
/*   Updated: 2024/08/06 18:35:58 by lbaumeis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftultra.h"

char	*ft_strdup(const char *c)
{
	size_t	b;
	char	*duplo;

	if (!c)
		return (NULL);
	b = ft_strlen(c) + 1;
	duplo = (char *)malloc((sizeof(char) * b));
	if (!duplo)
		return (NULL);
	ft_strlcpy(duplo, c, b);
	return (duplo);
}

/*
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
*/