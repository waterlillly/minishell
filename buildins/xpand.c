/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xpand.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbaumeis <lbaumeis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/02 12:40:29 by lbaumeis          #+#    #+#             */
/*   Updated: 2024/08/19 19:39:24 by lbaumeis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*xpand(t_pipex *p, char **token, int x)
{
	char	*temp;

	if (!p || !token || !token[x])
		return (NULL);
	temp = NULL;
	temp = remove_quotes(token[x]);
	if (check_d_quotes(token[x]) == true
		&& valid_env(p, ft_substr(temp, 1, ft_strlen(temp) - 1)))
		return (get_env(p, ft_substr(temp, 1, ft_strlen(temp) - 1)));
	else if (check_d_quotes(token[x]) == false && check_s_quotes(token[x]) == false)
		return (get_env(p, ft_substr(token[x], 1, ft_strlen(token[x]) - 1)));
	else
		return (temp);
	return (NULL);
}
