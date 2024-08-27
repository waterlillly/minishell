/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xpand.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbaumeis <lbaumeis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/02 12:40:29 by lbaumeis          #+#    #+#             */
/*   Updated: 2024/08/27 17:34:10 by lbaumeis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*rm_out_q(char *tok)
{
	if ((tok[0] == '\'' && tok[ft_strlen(tok) - 1] == '\'')
		|| (tok[0] == '\"' && tok[ft_strlen(tok) - 1] == '\"'))
		return (ft_substr(tok, 1, ft_strlen(tok) - 2));
	else
		return (tok);
}

char	*xpand(t_pipex *p, char **token, int x)
{
	char	*temp;
	char	*temp1;
	char	*temp2;

	if (!p || !token || !token[x])
		return (NULL);
	temp = NULL;
	temp1 = NULL;
	temp2 = NULL;
	temp = rm_out_q(token[x]);
	temp1 = ft_substr(temp, 1, ft_strlen(temp) - 1);
	if ((check_d_q(token[x]) == true || (check_d_q(token[x]) == false
		&& check_s_q(token[x]) == false)) && temp[0] == '$'
		&& !valid_env(p, temp1))
		return (free(temp), free(temp1), temp = NULL, temp1 = NULL, NULL);
	else if ((check_d_q(token[x]) == true
		|| (check_d_q(token[x]) == false && check_s_q(token[x]) == false))
		&& valid_env(p, temp1))
	{
		temp2 = get_env(p, temp1);
		return (free(temp1), temp1 = NULL, temp2);
	}
	else
		return (free(temp1), temp1 = NULL, temp);
}
