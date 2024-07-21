/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbaumeis <lbaumeis@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 16:39:36 by lbaumeis          #+#    #+#             */
/*   Updated: 2024/06/25 14:28:53 by lbaumeis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	int		i;
	char	find;
	char	*str;

	i = 0;
	if (!s)
		return (NULL);
	find = (char)c;
	str = (char *)s;
	while (str[i])
	{
		if (str[i] == find)
			return (&str[i]);
		else
			i++;
	}
	if (find == '\0')
		return (&str[i]);
	else
		return (NULL);
}
