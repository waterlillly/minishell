/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp_bool.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbaumeis <lbaumeis@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/02 14:55:27 by lbaumeis          #+#    #+#             */
/*   Updated: 2024/08/14 20:51:00 by lbaumeis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

bool	ft_strcmp_bool(const char *s1, const char *s2)
{
	size_t	x;
	size_t	len_s1;
	size_t	len_s2;

	x = 0;
	if (!s1 || !s2)
		return (false);
	len_s1 = ft_strlen(s1);
	len_s2 = ft_strlen(s2);
	if (len_s1 != len_s2)
		return (false);
	while (s1[x] && s2[x] && s1[x] == s2[x])
		x++;
	if (x == len_s1)
		return (true);
	return (false);
}
