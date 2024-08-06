/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printptr.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbaumeis <lbaumeis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/28 13:23:09 by lbaumeis          #+#    #+#             */
/*   Updated: 2024/08/06 18:34:23 by lbaumeis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftultra.h"

int	ft_printptr(void *ptr)
{
	int			count;
	long int	p;

	count = 0;
	p = (long int)ptr;
	if (p == 0)
		return (ft_printstr("(nil)"));
	if ((long long int)p < -9223372036854775807)
		return (ft_printstr("0x8000000000000000"));
	if ((long long int)p < 0)
		return (ft_printstr("0xffffffffffffffff"));
	else
	{
		count += ft_printstr("0x");
		count += ft_printnbr('x', p, 16);
	}
	return (count);
}
