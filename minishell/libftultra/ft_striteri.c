/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striteri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbaumeis <lbaumeis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/26 03:51:17 by lbaumeis          #+#    #+#             */
/*   Updated: 2024/08/06 18:36:02 by lbaumeis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftultra.h"

void	ft_striteri(char *s, void (*f)(unsigned int, char *))
{
	unsigned int	i;

	i = 0;
	if (!s || !f)
		return ;
	while (s[i] != '\0')
	{
		f(i, &s[i]);
		i++;
	}
}

/*
void	ft_striteri(char *s, void (*f)(unsigned int, char*))
{
	int		len;
	int		i;

	len = ft_strlen(s);
	i = -1;
	while (++i < len)
		(*f)(i, &s[i]);
}
*/