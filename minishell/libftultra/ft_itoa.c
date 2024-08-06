/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbaumeis <lbaumeis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 16:46:12 by lbaumeis          #+#    #+#             */
/*   Updated: 2024/08/06 18:31:24 by lbaumeis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftultra.h"

static int	ft_nbrlen(int nbr)
{
	int	len;

	len = 0;
	if (nbr <= 0)
	{
		len++;
		nbr *= (-1);
	}
	while (nbr > 0)
	{
		len++;
		nbr /= 10;
	}
	return (len);
}

static int	ft_times_ten(int len)
{
	int	tim;

	tim = 1;
	if (len == 1)
		return (1);
	while (len > 1)
	{
		tim *= 10;
		len--;
	}
	return (tim);
}

static char	*ft_extra(void)
{
	char	*result;

	result = ft_strdup("-2147483648");
	if (!result)
	{
		free(result);
		return (0);
	}
	return (result);
}

static char	*ft_resultoa(int n, int len, int backup, char *result)
{
	int	i;

	i = 0;
	if (n < 0)
	{
		n *= (-1);
		result[i] = '-';
		i++;
		len--;
	}
	while (i < backup)
	{
		result[i] = ((n / ft_times_ten(len)) % 10 + 48);
		i++;
		len--;
	}
	result[i] = '\0';
	return (result);
}

char	*ft_itoa(int n)
{
	int		len;
	int		backup;
	char	*result;

	if (n == -2147483648)
		return (ft_extra());
	len = ft_nbrlen(n);
	backup = len;
	result = (char *)malloc(sizeof(char) * len + 1);
	if (!result)
		return (0);
	result = ft_resultoa(n, len, backup, result);
	if (!result)
	{
		free(result);
		return (0);
	}
	return (result);
}

/*
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
*/