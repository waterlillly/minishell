/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 21:47:05 by codespace         #+#    #+#             */
/*   Updated: 2023/09/13 23:22:59 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	int		len;
	char	*out;
	int		i;

	len = ft_strlen(s);
	i = -1;
	out = (char *)ft_calloc((len + 1), sizeof(char));
	if (!out)
		return (NULL);
	while (++i < len)
		out[i] = (*f)(i, s[i]);
	return (out);
}
