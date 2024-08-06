/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbaumeis <lbaumeis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/26 03:36:08 by lbaumeis          #+#    #+#             */
/*   Updated: 2024/08/06 18:31:09 by lbaumeis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftultra.h"

void	ft_putnbr_fd(int n, int fd)
{
	if (fd < 0)
		return ;
	if (n == -2147483648)
		ft_putstr_fd("-2147483648", fd);
	else if (n < 0 && n > -2147483648)
	{
		ft_putchar_fd('-', fd);
		n = -n;
		ft_putnbr_fd(n, fd);
	}
	else if (n < 10)
		ft_putchar_fd(n + 48, fd);
	else
	{
		ft_putnbr_fd(n / 10, fd);
		ft_putnbr_fd(n % 10, fd);
	}
}

/*
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
*/