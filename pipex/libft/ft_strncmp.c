/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbaumeis <lbaumeis@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 16:40:39 by lbaumeis          #+#    #+#             */
/*   Updated: 2024/06/25 14:46:39 by lbaumeis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

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
