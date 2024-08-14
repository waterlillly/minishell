/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str_lower.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbaumeis <lbaumeis@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/27 16:44:57 by lbaumeis          #+#    #+#             */
/*   Updated: 2024/08/14 15:50:27 by lbaumeis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_str_lower(char *s)
{
	char	*new;

	if (!s)
		return (NULL);
	new = NULL;
	new = malloc(sizeof(char) * (ft_strlen(s) + 1));
	if (!new)
		return (NULL);
	while (*s)
	{
		*new = (char)(ft_tolower(*s));
		new++;
		s++;
	}
	*new = '\0';
	free(s);
	s = NULL;
	return (new);
}
