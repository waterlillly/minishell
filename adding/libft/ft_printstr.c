/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printstr.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbaumeis <lbaumeis@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/28 06:02:45 by lbaumeis          #+#    #+#             */
/*   Updated: 2024/08/14 15:49:55 by lbaumeis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

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
