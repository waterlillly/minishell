/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 16:46:12 by lbaumeis          #+#    #+#             */
/*   Updated: 2023/10/14 08:20:21 by lbaumeis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

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
