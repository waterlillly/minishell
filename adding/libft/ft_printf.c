/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbaumeis <lbaumeis@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/28 05:25:42 by lbaumeis          #+#    #+#             */
/*   Updated: 2024/08/14 15:49:45 by lbaumeis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_printf(const char *format, ...)
{
	va_list	args;
	int		count;
	int		i;

	va_start(args, format);
	count = 0;
	i = 0;
	if (!format || format == NULL)
		count += ft_printstr("(null)");
	while (format[i] != '\0')
	{
		if (format[i] == '%')
		{
			i++;
			count += ft_decideformat(args, format, i);
		}
		else
			count += ft_printchar((int)format[i]);
		i++;
	}
	va_end(args);
	return (count);
}
