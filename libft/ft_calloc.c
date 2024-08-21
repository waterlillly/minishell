/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbaumeis <lbaumeis@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 16:38:01 by lbaumeis          #+#    #+#             */
/*   Updated: 2024/08/14 15:47:22 by lbaumeis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*p;

	p = malloc(nmemb * size);
	if (!p)
		return (NULL);
	ft_bzero(p, nmemb * size);
	return (p);
}

/*
void	*ft_calloc(size_t nmemb, size_t size)
{
	char	*out;

	if (nmemb * size == 0 || (nmemb * size) / size != nmemb)
	{
		nmemb = 0;
		size = 1;
	}
	if (size >= 1 && size <= 8)
	{
		out = (char *)malloc(size * nmemb);
		if (!out)
			return (NULL);
		ft_bzero(out, nmemb * size);
	}
	else
		return (NULL);
	return ((void *)out);
}
*/