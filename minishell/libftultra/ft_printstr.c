/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printstr.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbaumeis <lbaumeis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/28 06:02:45 by lbaumeis          #+#    #+#             */
/*   Updated: 2024/08/06 18:34:26 by lbaumeis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftultra.h"

int	ft_printstr(char *s)
{
	int	count;

	count = 0;
	if (!s)
		s = "(null)";
	while (*s != '\0')
	{
		count += ft_printchar(*s);
		s++;
	}
	return (count);
}
