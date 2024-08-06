/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str_upper.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbaumeis <lbaumeis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/27 16:35:48 by lbaumeis          #+#    #+#             */
/*   Updated: 2024/08/06 18:35:40 by lbaumeis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftultra.h"

char	*ft_str_upper(char *s)
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
		*new = (char)(ft_toupper(*s));
		new++;
		s++;
	}
	*new = '\0';
	free(s);
	s = NULL;
	return (new);
}
