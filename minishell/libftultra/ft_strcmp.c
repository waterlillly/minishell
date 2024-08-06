/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbaumeis <lbaumeis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 17:28:17 by lbaumeis          #+#    #+#             */
/*   Updated: 2024/08/06 18:35:54 by lbaumeis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftultra.h"

//not original one
int	ft_strcmp(const char *s1, const char *s2)
{
	size_t	x;
	size_t	len_s1;
	size_t	len_s2;

	x = 0;
	if (!s1 || !s2)
		return (0);
	len_s1 = ft_strlen(s1);
	len_s2 = ft_strlen(s2);
	if (len_s1 != len_s2)
		return (0);
	while (s1[x] && s2[x] && s1[x] == s2[x])
		x++;
	if (x == len_s1)
		return (1);
	return (0);
}
/*
int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] == s2[i] && s1[i] != '\0' && s2[i] != '\0')
		i++;
	return (s1[i] - s2[i]);
}
*/