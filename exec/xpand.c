/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xpand.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbaumeis <lbaumeis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/02 12:40:29 by lbaumeis          #+#    #+#             */
/*   Updated: 2024/10/06 17:21:53 by lbaumeis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

bool	only_dollars(char *tok)
{
	int	x;

	x = 0;
	while (tok[x] == '$')
	{
		x++;
		if (!tok[x + 1])
			return (true);
	}
	return (false);
}

char	*rm_out_q(char *tok)
{
	if ((tok[0] == '\'' && tok[ft_strlen(tok) - 1] == '\'')
		|| (tok[0] == '\"' && tok[ft_strlen(tok) - 1] == '\"'))
		return (ft_substr(tok, 1, ft_strlen(tok) - 2));
	else
		return (tok);
}

int	multi_q(char *token)
{
	int	x;
	int	c;

	x = 0;
	c = 0;
	while (token[x])
	{
		if (token[x] == '\"' || token[x] == '\'')
			c++;
		x++;
	}
	return (c);
}

char	*rm_q(char *token)
{
	char	*new;
	int		q;
	int		x;
	int		y;

	new = NULL;
	x = 0;
	y = 0;
	if (check_d_q(token) <= 0 && !check_s_q(token))
		return (token);
	q = multi_q(token);
	new = ft_calloc((ft_strlen(token) - q + 1), sizeof(char));
	if (!new)
		return (NULL);
	while (token[x] && x < (int)ft_strlen(token) - q + 1)
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
	char	*temp2;

	if (!p || !token || !token[x])
		return (NULL);
	temp = NULL;
	temp2 = NULL;
	temp = rm_out_q(token[x]);
	if (!check_s_q(token[x]) && ft_strcmp_bool(token[x], "$?"))
		return (free(temp), ft_itoa_long(p->status));
	else if (only_dollars(token[x]) && ((dollar_count(token[x]) == 1 && even_q(token[x]))
		|| (dollar_count(token[x]) == 1)))
		return ("");
	else if (!check_s_q(token[x]) && temp[0] == '$' && temp[1] != '$'
		&& temp[1] != '\0' && !valid_env(p, ft_substr(temp, 1, ft_strlen(temp) - 1)))
		return (free(temp), "");
	else if (!check_s_q(token[x]) && valid_env(p, ft_substr(temp, 1, ft_strlen(temp) - 1)))
	{
		temp2 = get_env(p, ft_substr(temp, 1, ft_strlen(temp) - 1));
		return (temp2);
	}
	else if (s_out_q(token[x]) || d_out_q(token[x]))
		return (temp);
	else
		return (rm_q(token[x]));
}
