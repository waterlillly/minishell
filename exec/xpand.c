/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xpand.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbaumeis <lbaumeis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/02 12:40:29 by lbaumeis          #+#    #+#             */
/*   Updated: 2024/10/17 17:34:05 by lbaumeis         ###   ########.fr       */
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

/*
	only space -> return (" ");
	check if space at front and back & save somehow
	-> then strtrim space off
	go though leftover + count spaces (do not count the one right before a diff character)
	calloc for strlen(trimmed) + 3 - counted spaces
*/

static bool	only_space(char *s)
{
	int	i;
	
	if (!s)
		return (false);
	i = 0;
	while (s[i] && s[i] == ' ')
		i++;
	if (s[i] == '\0')
		return (true);
	return (false);
}

static char	*trim_space(char *s)
{
	int		i;
	int		x;
	char	*trim;
	char	*new;

	if (!s)
		return (NULL);
	else if (only_space(s))
	{
		new = ft_strdup(" ");	
		return (new);
	}
	trim = ft_strtrim(s, " ");
	if (!trim)
		return (NULL);
	i = 0;
	x = 0;
	while (trim && trim[i])
	{
		while (trim[i] && trim[i] != ' ')
		{
			x++;
			i++;
		}
		if (trim[i] && trim[i] == ' ')
		{
			x++;
			while (trim[i] && trim[i] == ' ')
				i++;
		}
	}
	if (s[0] == ' ')
		x++;
	if (s[ft_strlen(s) - 1] == ' ')
		x++;
	new = ft_calloc(x + 1, sizeof(char));
	if (!new)
		return (NULL);
	i = 0;
	x = 0;
	if (s[i] == ' ')
	{
		new[x] = ' ';
		x++;
	}
	while (trim[i])
	{
		while (trim[i] && trim[i] != ' ')
		{
			new[x] = trim[i];
			i++;
			x++;
		}
		if (trim[i] == ' ')
		{
			new[x] = ' ';
			i++;
			x++;
			while (trim[i] && trim[i] == ' ')
				i++;
		}
	}
	if (s[ft_strlen(s) - 1] == ' ')
		new[x] = ' ';
	return (new);
}

char	*xpand(t_pipex *p, char **token, int x, int lead)
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
	if (!s_out_q(token[x]) && (ft_strcmp_bool(token[x], "$?") || ft_strcmp_bool(rm_qout, "$?")))
		return (free(temp1), free(temp2), free(rm_qout), free(temp2_sub), ft_itoa_long(p->status));
	else if ((!s_out_q(token[x]) && rm_qout[0] == '$'
		&& rm_qout[1] != '\0' && rm_qout[1] != '$'
		&& !valid_env(p, temp1)) || (ft_strcmp_bool(token[x], "$") && token[x + 1]
		&& is_quote(token[x + 1][0])))
		return (free(temp1), free(temp2), free(rm_qout), free(temp2_sub), ft_strdup(""));
	else if (!s_out_q(token[x]) && valid_env(p, temp1) && lead == 1)
	{
		temp = get_env(p, temp1);
		(free(temp1), temp1 = NULL, free(temp2), free(rm_qout), free(temp2_sub));
		if (!temp)
			return (NULL);
		temp1 = trim_space(temp);
		free(temp);
		temp = NULL;
		if (!temp1)
			return (NULL);
		if (temp1 && (x == 0 || !token[x - 1]) && temp1[0] == ' ' && !token[x + 1] && temp1[ft_strlen(temp1) - 1] == ' ')
			return (temp = ft_substr(temp1, 1, ft_strlen(temp1) - 2));
		else if (temp1 && !token[x - 1] && temp1[0] == ' ')
			return (temp = ft_substr(temp1, 1, ft_strlen(temp1) - 1));
		else if (temp1 && !token[x + 1] && temp1[ft_strlen(temp1) - 1] == ' ')
			return (temp = ft_substr(temp1, 0, ft_strlen(temp1) - 1));
		return (temp1);
	}
	else if (!s_out_q(token[x]) && valid_env(p, temp1) && lead == 0)
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
