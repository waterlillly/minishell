/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 23:58:26 by codespace         #+#    #+#             */
/*   Updated: 2023/09/14 00:10:43 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	int		tmp;

	tmp = n;
	if (n == -2147483648)
		ft_putstr_fd("-2147483648", fd);
	else if (tmp < 0)
	{
		ft_putstr_fd("-", fd);
		tmp = -tmp;
		ft_putnbr_fd(tmp, fd);
	}
	else if (tmp >= 10)
	{
		ft_putnbr_fd(tmp / 10, fd);
		ft_putnbr_fd(tmp % 10, fd);
	}
	else
		ft_putchar_fd(tmp + 48, fd);
}
