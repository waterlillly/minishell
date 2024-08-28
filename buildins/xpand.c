/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xpand.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbaumeis <lbaumeis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/02 12:40:29 by lbaumeis          #+#    #+#             */
/*   Updated: 2024/08/28 18:07:15 by lbaumeis         ###   ########.fr       */
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

int	multi_d_q(char *token)
{
	int	x;
	int	c;

	x = 0;
	c = 0;
	while (token[x])
	{
		if (token[x] == '\"')
			c++;
		x++;
	}
	return (c);
}
/*
char	**sep_d_q(char *token)
{
	char	**tok;

	tok = NULL;
	tok = ft_split(token, '\"');
	if (!tok)
		return (NULL);
	
}
*/

char	*rm_inner_d_q(char *token)
{
	char	*new;
	int		q;
	int		x;
	int		y;

	new = NULL;
	x = 1;
	y = 0;
	q = multi_d_q(token);
	new = ft_calloc((ft_strlen(token) - q + 1), sizeof(char));
	if (!new)
		return (NULL);
	while (token[x] && x < (int)ft_strlen(token) - 1)
	{
		if (token[x] == '\"')
			x++;
		else
			new[y++] = token[x++];
	}
	return (new);
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
	else if (token[x][0] == '\'' && token[x][ft_strlen(token[x]) - 1] == '\'')
		return (free(temp1), temp1 = NULL, temp);
	else if (token[x][0] == '\"' && token[x][ft_strlen(token[x]) - 1] == '\"')
		return (free(temp1), temp1 = NULL, rm_inner_d_q(token[x]));
	else
		return (free(temp1), temp1 = NULL, remove_quotes(temp));
}
