/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_decideformat.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbaumeis <lbaumeis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 20:54:11 by lbaumeis          #+#    #+#             */
/*   Updated: 2024/08/06 18:29:51 by lbaumeis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftultra.h"

int	ft_decideformat(va_list args, const char *format, int i)
{
	int	count;

	count = 0;
	if (format[i] == 'c')
		count += ft_printchar(va_arg(args, int));
	else if (format[i] == 's')
		count += ft_printstr(va_arg(args, char *));
	else if (format[i] == 'p')
		count += ft_printptr(va_arg(args, void *));
	else if (format[i] == '%')
		count += ft_printchar(37);
	else if (format[i] == 'd' || format[i] == 'i' || format[i] == 'u')
		count += ft_printnbr(format[i], va_arg(args, int), 10);
	else if (format[i] == 'x' || format[i] == 'X')
		count += ft_printnbr(format[i], va_arg(args, unsigned int), 16);
	else
		count += ft_printchar((int)format[i]);
	return (count);
}
