/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbaumeis <lbaumeis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 16:40:39 by lbaumeis          #+#    #+#             */
/*   Updated: 2024/08/06 18:32:51 by lbaumeis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftultra.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	x;

	x = 0;
	if (!s1 || !s2 || n == 0)
		return (0);
	while (s1[x] == s2[x] && x < n - 1 && s1[x] != '\0')
		x++;
	return ((unsigned char)s1[x] - (unsigned char)s2[x]);
}

/*
int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t			i;
	unsigned char	*str1;
	unsigned char	*str2;

	str1 = (unsigned char *)s1;
	str2 = (unsigned char *)s2;
	i = 0;
	if (n == 0)
		return (0);
	while (str1[i] == str2[i] && str1[i] != '\0'
		&& str2[i] != '\0' && (i < n - 1))
		i++;
	return (str1[i] - str2[i]);
}
*/