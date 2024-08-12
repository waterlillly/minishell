/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xpand.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbaumeis <lbaumeis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/02 12:40:29 by lbaumeis          #+#    #+#             */
/*   Updated: 2024/08/11 15:32:50 by lbaumeis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../exec.h"

char	*xpand(t_pipex *p, char **token, int x)
{
	char	*temp;

	temp = NULL;
	if (!token || !token[x])
		return (NULL);
	temp = get_env(p, ft_substr(token[x], 1, ft_strlen(token[x]) - 1));
	if (!temp)
		return (NULL);//error(p, "substr", p->status);
	return (temp);
}
