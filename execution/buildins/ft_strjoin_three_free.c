/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin_three_free.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbaumeis <lbaumeis@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 14:08:21 by lbaumeis          #+#    #+#             */
/*   Updated: 2024/08/01 19:13:55 by lbaumeis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "buildins.h"

char	*ft_strjoin_space_free(char *s1, const char *s2)
{
	char	*first;
	char	*result;

	first = NULL;
	result = NULL;
	if (!s1 || !s2)
		return (NULL);
	first = ft_strjoin_free_one(s1, " ");
	if (!first)
		return (NULL);
	result = ft_strjoin_free_one(first, s2);
	if (!result)
		return (NULL);
	return (result);
}
