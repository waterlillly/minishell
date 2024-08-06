/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isprint_extend.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbaumeis <lbaumeis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/06 16:48:32 by lbaumeis          #+#    #+#             */
/*   Updated: 2024/08/06 18:30:42 by lbaumeis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftultra.h"

int	ft_isprint_extend(int n)
{
	if (n >= 32 && n <= 126)
		return (1);
	else if (n >= 128 && n <= 255)
		return (1);
	else
		return (0);
}
/*
int	main(void)
{
	ft_isprint(55);
	ft_isprint(127);
	return (0);
}
*/
