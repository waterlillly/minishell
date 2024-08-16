/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c	                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgardesh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 13:22:56 by mgardesh          #+#    #+#             */
/*   Updated: 2023/09/05 13:23:23 by mgardesh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_putnbr(char *str, int nb)
{
	int		tmp;
	char	temp;

	if (nb == -2147483648)
	{
		ft_strlcat(str, "-2147483648", 12);
		return ;
	}
	tmp = nb;
	if (tmp < 0)
	{
		ft_strlcpy(str, "-", 2);
		tmp = -tmp;
	}
	if (tmp >= 10)
	{
		ft_putnbr(str, tmp / 10);
		ft_putnbr(str, tmp % 10);
	}
	else
	{
		temp = tmp + '0';
		ft_strlcat(str, &temp, 2 + ft_strlen(str));
	}
}

char	*ft_itoa(int n)
{
	char	*out;
	size_t	i;
	int		tmp;

	i = 0;
	tmp = n;
	if (n <= 0)
	{
		n *= -1;
		i++;
	}
	while (n != 0)
	{
		n /= 10;
		i++;
	}
	out = (char *)malloc((i + 1) * sizeof(char));
	if (!out)
		return (NULL);
	out[0] = '\0';
	ft_putnbr(out, tmp);
	return (out);
}
