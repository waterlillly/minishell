/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xpand.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbaumeis <lbaumeis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/02 12:40:29 by lbaumeis          #+#    #+#             */
/*   Updated: 2024/10/12 19:38:37 by lbaumeis         ###   ########.fr       */
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
	// if (check_d_q(token) <= 0 && !check_s_q(token))
	// 	return (ft_strdup(token));
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

	if (!p || !token || !token[x])
		return (NULL);
	temp = NULL;
	temp1 = NULL;
	temp1 = ft_substr(rm_out_q(token[x]), 1, ft_strlen(rm_out_q(token[x])) - 1);
	if (!s_out_q(token[x]) && ft_strcmp_bool(token[x], "$?"))
		return (temp = ft_itoa_long(p->status), free(temp1), temp);
	else if (!s_out_q(token[x]) && rm_out_q(token[x])[0] == '$' && rm_out_q(token[x])[1] != '\0' && rm_out_q(token[x])[1] != '$' && !valid_env(p, temp1))
		return (free(temp1), ft_strdup(""));
	else if (!s_out_q(token[x]) && valid_env(p, temp1))
		return (temp = get_env(p, temp1), free(temp1), temp);
	else if (s_out_q(token[x]) || d_out_q(token[x]))
		return (free(temp1), temp = rm_out_q(token[x]));
	else
		return (free(temp1), temp = rm_q(token[x]));
}

// char	*xpand(t_pipex *p, char **token, int x)
// {
// 	char	*temp;
// 	char	*temp1;
// 	char	*temp2;
// 	char	*tmp_num;

// 	if (!p || !token || !token[x])
// 		return (NULL);
// 	temp = NULL;
// 	temp1 = NULL;
// 	temp2 = NULL;
// 	temp = rm_out_q(token[x]);
// 	temp1 = ft_substr(temp, 1, ft_strlen(temp) - 1);
// 	if (!check_s_q(token[x]) && ft_strcmp_bool(token[x], "$?"))
// 		return (free(temp), free(temp1), tmp_num = ft_itoa_long(p->status),
// 		temp = ft_strdup(tmp_num), free(tmp_num), temp);
// 	else if (token[x] && ((only_dollars(token[x]) && ((dollar_count(token[x]) == 1 && even_q(token[x])) || dollar_count(token[x]) == 1))
// 		|| (!check_s_q(token[x]) && temp[0] == '$' && temp[1] != '$' && temp[1] != '\0' && !valid_env(p, temp1))))
// 		return (free(temp), free(temp1), ft_strdup(""));
// 	else if (!check_s_q(token[x]) && valid_env(p, temp1))
// 	{
// 		temp2 = get_env(p, temp1);
// 		return (free(temp), free(temp1), temp2);
// 	}
// 	else if (s_out_q(token[x]) || d_out_q(token[x]))
// 		return (free(temp1), temp);
// 	else
// 		return (free(temp), free(temp1), rm_q(token[x]));
// }
