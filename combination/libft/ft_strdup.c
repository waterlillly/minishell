/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbaumeis <lbaumeis@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 16:40:01 by lbaumeis          #+#    #+#             */
/*   Updated: 2024/06/25 14:30:40 by lbaumeis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

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
