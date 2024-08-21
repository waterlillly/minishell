/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dtoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbaumeis <lbaumeis@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/21 20:46:53 by lbaumeis          #+#    #+#             */
/*   Updated: 2024/08/14 15:47:29 by lbaumeis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <math.h>

static int	ft_dbl_len(double d)
{
	int		len;
	double	temp;

	temp = fabs(d);
	len = 0;
	while (temp!= 0)
	{
		temp /= 10;
		len++;
	}
	return (len);
}

static int	ft_dbl_times_ten(int len)
{
	int	times;

	times = 1;
	while (len > 0)
	{
		times *= 10;
		len--;
	}
	return (times);
}

static char	*ft_dbltoa(double d, int prec)
{
	char	*str;
	int		i;
	int		len;
	int		decimals;

	len = ft_dbl_len(d);
	str = (char *)malloc((len + 2 + prec + 2) * sizeof(char));
	if (!str)
		return (NULL);
	if (d < 0)
	{
		str[0] = '-';
		d *= -1;
		len++;
	}
	i = 0;
	while (d >= 1)
	{
		str[i++] = (d / ft_dbl_times_ten(len)) + '0';
		d -= ft_dbl_times_ten(len) * (d / ft_dbl_times_ten(len));
		len--;
	}
	str[i++] = '.';
	decimals = 0;
	while (decimals < prec && i < len + 2)
	{
		d *= 10;
		str[i++] = (int)d + '0';
		decimals++;
	}
	str[i] = '\0';
	return (str);
}

char	*ft_dtoa(double d)
{
	int		len;
	char	*str;
	int		prec;
	
	prec = 8;
	len = ft_dbl_len(d);
	str = ft_dbltoa(d, prec);
	if (!str)
		return (NULL);
	return (str);
}
