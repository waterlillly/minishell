/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xpand.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbaumeis <lbaumeis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/02 12:40:29 by lbaumeis          #+#    #+#             */
/*   Updated: 2024/08/07 11:32:21 by lbaumeis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "buildins.h"

char	*xpand(t_buildins *vars, char **token, int x)
{
	char	*temp;

	temp = NULL;
	temp = get_env(vars, ft_substr(token[x], 1, ft_strlen(token[x] - 1)));
	if (!temp)
		error("substr");
	return (temp);
}
