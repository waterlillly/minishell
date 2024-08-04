/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbaumeis <lbaumeis@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/04 18:54:32 by lbaumeis          #+#    #+#             */
/*   Updated: 2024/08/04 20:05:55 by lbaumeis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "buildins.h"

void	unset(t_buildins *vars, char **token)
{
	int	x;

	x = find_arg(token, "unset");
	if (x == -1)
		return ;
	if (token[x + 1][0] == '$')
		err_or("not a valid identifier");
	if (valid_env(vars, token[x + 1]) == true)
	
}