/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xpand.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbaumeis <lbaumeis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/02 12:40:29 by lbaumeis          #+#    #+#             */
/*   Updated: 2024/10/15 12:17:21 by lbaumeis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

bool	only_dollars(char *tok)
{
	int	x;

	x = 0;
	while (tok[x] && tok[x] == '$')
	{
		x++;
		if (!tok[x])
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
		return (ft_strdup(tok));
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
	q = multi_q(token);
	new = ft_calloc((ft_strlen(token) - q + 1), sizeof(char));
	if (!new)
		return (NULL);
	while (token[x] && x < (int)ft_strlen(token) - q + 1)
	{
		if (token[x] == '\"' || token[x] == '\'')
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
	temp1 = ft_substr(rm_out_q(token[x]), 1, ft_strlen(rm_out_q(token[x])) - 1);
	temp2 = rm_out_q(rm_out_q(token[x]));
	if (!s_out_q(token[x]) && ft_strcmp_bool(token[x], "$?"))
		return (temp = ft_itoa_long(p->status), free(temp1), free(temp2), temp);
	else if ((!s_out_q(token[x]) && rm_out_q(token[x])[0] == '$'
		&& rm_out_q(token[x])[1] != '\0' && rm_out_q(token[x])[1] != '$'
		&& !valid_env(p, temp1)) || (ft_strcmp_bool(token[x], "$") && token[x + 1] && is_quote(token[x + 1][0])))
		return (free(temp1), free(temp2), ft_strdup(""));
	else if (!s_out_q(token[x]) && valid_env(p, temp1))
		return (temp = get_env(p, temp1), free(temp1), free(temp2), temp);
	else if (d_out_q(token[x]) && s_out_q(rm_out_q(token[x]))
		&& valid_env(p, ft_substr(temp2, 1, ft_strlen(temp2) - 1)))
	{
		free(temp1);
		temp1 = NULL;
		temp1 = get_env(p, ft_substr(temp2, 1, ft_strlen(temp2) - 1));
		free(temp2);
		temp2 = NULL;
		temp2 = ft_strjoin("\'", ft_strjoin(temp1, "\'"));
		return (free(temp1), temp2);
	}
	else if (s_out_q(token[x]) || d_out_q(token[x]))
		return (free(temp1), free(temp2), temp = rm_out_q(token[x]));
	else
		return (free(temp1), free(temp2), temp = rm_q(token[x]));
}
