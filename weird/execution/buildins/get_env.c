/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbaumeis <lbaumeis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 16:45:55 by lbaumeis          #+#    #+#             */
/*   Updated: 2024/07/29 13:25:17 by lbaumeis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "buildins.h"

char	*get_env(t_buildins *vars, char *str)
{
	int		x;
	size_t	len;
	char	*result;

	x = 0;
	len = 0;
	result = NULL;
	while (vars->menv[x])
	{
		if (ft_strnstr(vars->menv[x], str, ft_strlen(str)) == &(vars->menv[x][0]))
		{
			len = ft_strlen(vars->menv[x]) - ft_strlen(str);
			result = malloc(sizeof(char) * len);
			if (!result)
				return (NULL);
			result = ft_substr(vars->menv[x], ft_strlen(str) + 1, len - 1);
			if (!result)
				return (NULL);
			return (result);
		}
		x++;
	}
	return (NULL);
}
