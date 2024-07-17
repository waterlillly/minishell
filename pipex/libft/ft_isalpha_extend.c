/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalpha_extend.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbaumeis <lbaumeis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 16:51:17 by lbaumeis          #+#    #+#             */
/*   Updated: 2024/07/15 14:33:12 by lbaumeis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isalpha_extend(int n)
{
	if ((n >= 65 && n <= 90) || (n >= 97 && n <= 122))
		return (1);
	else if (n >= 192 && n <= 214)
		return (1);
	else if (n >= 217 && n <= 246)
		return (1);
	else if (n >= 249 && n <= 255)
		return (1);
	else
		return (0);
}
/*
int	main(void)
{
	char	s;

	s = 'S';
	ft_isalpha(50);
	ft_isalpha('x');
	ft_isalpha('P');
	ft_isalpha(-2);
	ft_isalpha(s);
	return (0);
}
*/
