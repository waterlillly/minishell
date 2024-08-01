/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin_three_free.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbaumeis <lbaumeis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 14:08:21 by lbaumeis          #+#    #+#             */
/*   Updated: 2024/08/01 14:50:05 by lbaumeis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "buildins.h"

char	*ft_strjoin_space_free(char *s1, char *s2)
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
	result = ft_strjoin_free_both(first, s2);
	if (!result)
		return (NULL);
	return (result);
}
