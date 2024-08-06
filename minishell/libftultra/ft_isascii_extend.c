/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isascii_extend.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbaumeis <lbaumeis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/06 16:31:52 by lbaumeis          #+#    #+#             */
/*   Updated: 2024/08/06 18:30:23 by lbaumeis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
included the extended ascii table, so it stops at 255, not 127
*/
#include "libftultra.h"

int	ft_isascii_extend(int n)
{
	if (n >= 0 && n <= 255)
		return (1);
	else
		return (0);
}
/*
int	main(void)
{
	ft_isascii('e');
	ft_isascii(3);
	ft_isascii(129);
	return (0);
}
*/
