/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc_2d.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbaumeis <lbaumeis@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/05 11:56:05 by codespace         #+#    #+#             */
/*   Updated: 2024/08/14 15:50:21 by lbaumeis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	**ft_realloc_2d(char **in, int add)
{
	int 	i;
	char	**out;

	if (!add)
		return (NULL);
	i = ft_strlen_2d(in);
	out = ft_calloc(i + add + 1, sizeof(char *));
	if (!out)
		return(ft_free_2d(in), NULL);
	i = -1;
	while (in && in[++i])
	{
		out[i] = ft_strdup(in[i]);
		if (!out[i])
			return(ft_free_2d(in), ft_free_2d(out), NULL);
		free(in[i]);
	}
	if (in)
		free(in);
	return(out);
}
