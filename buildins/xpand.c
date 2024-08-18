/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xpand.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbaumeis <lbaumeis@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/02 12:40:29 by lbaumeis          #+#    #+#             */
/*   Updated: 2024/08/14 14:35:46 by lbaumeis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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
