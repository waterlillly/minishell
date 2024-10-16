/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xpand.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgardesh <mgardesh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/02 12:40:29 by lbaumeis          #+#    #+#             */
/*   Updated: 2024/10/15 15:34:02 by mgardesh         ###   ########.fr       */
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
	char	*rm_qout;
	char	*temp2_sub;

	if (!p || !token || !token[x])
		return (NULL);
	temp = NULL;
	rm_qout = rm_out_q(token[x]);
	temp1 = ft_substr(rm_qout, 1, ft_strlen(rm_qout) - 1);
	temp2 = rm_out_q(rm_qout);
	temp2_sub = ft_substr(temp2, 1, ft_strlen(temp2) - 1);
	if (!s_out_q(token[x]) && ft_strcmp_bool(token[x], "$?"))
		return (free(temp1), free(temp2), free(rm_qout), free(temp2_sub), ft_itoa_long(p->status));
	else if (!s_out_q(token[x]) && rm_qout[0] == '$'
		&& rm_qout[1] != '\0' && rm_qout[1] != '$'
		&& !valid_env(p, temp1))
		return (free(temp1), free(temp2), free(rm_qout), free(temp2_sub), ft_strdup(""));
	else if (!s_out_q(token[x]) && valid_env(p, temp1))
		return (temp = get_env(p, temp1), free(temp1), free(temp2), free(rm_qout), free(temp2_sub), temp);
	else if (d_out_q(token[x]) && s_out_q(rm_qout)
		&& valid_env(p, temp2_sub))
	{
		free(temp1);
		temp1 = NULL;
		temp1 = get_env(p, ft_substr(temp2, 1, ft_strlen(temp2) - 1));
		free(temp2);
		temp2 = NULL;
		temp2 = ft_strjoin("\'", ft_strjoin(temp1, "\'"));
		free(temp1);
		free(temp2_sub);
		return (temp2);
	}
	else if (s_out_q(token[x]) || d_out_q(token[x]))
		return (free(temp1), free(temp2), free(temp2_sub), rm_qout);
	else
		return (free(temp1), free(temp2), free(rm_qout), free(temp2_sub), rm_q(token[x]));
}
