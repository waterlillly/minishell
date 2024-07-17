/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printnbr.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbaumeis <lbaumeis@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/28 08:38:19 by lbaumeis          #+#    #+#             */
/*   Updated: 2023/11/13 14:46:10 by lbaumeis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_islower(char c)
{
	if (c >= 'a' && c <= 'z')
		return (1);
	else
		return (0);
}

static int	ft_isupper(char c)
{
	if (c >= 'A' && c <= 'Z')
		return (1);
	else
		return (0);
}

static int	ft_printhexa(char specifier, unsigned long int nbr)
{
	int		count;
	char	*set;

	count = 0;
	if (ft_isupper(specifier))
		set = "ABCDEF";
	else if (ft_islower(specifier))
		set = "abcdef";
	if (nbr == 10)
		count += ft_printchar(set[0]);
	else if (nbr == 11)
		count += ft_printchar(set[1]);
	else if (nbr == 12)
		count += ft_printchar(set[2]);
	else if (nbr == 13)
		count += ft_printchar(set[3]);
	else if (nbr == 14)
		count += ft_printchar(set[4]);
	else if (nbr == 15)
		count += ft_printchar(set[5]);
	return (count);
}

int	ft_printnbr(char specifier, long int nbr, int base)
{
	int	count;

	count = 0;
	if (specifier == 'u')
		nbr = (unsigned int)nbr;
	if (specifier == 'x' || specifier == 'X')
		nbr = (unsigned long int)nbr;
	if (nbr == -2147483648 && base == 10)
		count += ft_printstr("-2147483648");
	if (nbr < 0 && nbr > -2147483648 && base == 10)
	{
		count += ft_printchar('-');
		count += ft_printnbr(specifier, -nbr, base);
	}
	else if (nbr >= 0 && nbr < 10)
		count += ft_printchar(nbr + 48);
	else if (base == 16 && nbr >= 10 && nbr < base)
		count += ft_printhexa(specifier, nbr);
	else if (nbr >= base)
	{
		count += ft_printnbr(specifier, (nbr / base), base);
		count += ft_printnbr(specifier, (nbr % base), base);
	}
	return (count);
}
