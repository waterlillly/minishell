/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbaumeis <lbaumeis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/18 16:24:45 by lbaumeis          #+#    #+#             */
/*   Updated: 2024/08/27 16:10:26 by lbaumeis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*add_quotes(char *token)
{
	int		x;
	int		y;
	char	*new;

	x = 0;
	y = 0;
	new = NULL;
	if (!token)
		return (NULL);
	new = ft_calloc((ft_strlen(token) + 3), sizeof(char));
	if (!new)
		return (NULL);
	new[y] = '\"';
	y++;
	while (token[x])
		new[y++] = token[x++];
	new[y] = '\"';
	//new[y + 1] = '\0';
	return (new);
}

char	*remove_quotes(char *s)
{
	int		x;
	int		y;
	char	*temp;

	x = 0;
	y = 0;
	temp = NULL;
	if (!s || ft_strlen(s) < 2)
		return (NULL);
	else if (!check_d_q(s) && !check_s_q(s))
		return (s);
	temp = ft_calloc((ft_strlen(s) - 1), sizeof(char));
	if (!temp)
		return (NULL);
	while (s[x])
	{
		if (s[x] == '\"' || s[x] == '\'')
			x++;
		else
			temp[y++] = s[x++];
	}
	return (temp);
}

bool	check_d_q(char *token)
{
	int		x;
	bool	d_q;

	x = 0;
	d_q = false;
	if (!token)
		return (false);
	while (token[x])
	{
		if (token[x] == '\"')
		{
			d_q = true;
			x++;
			break ;
		}
		x++;
	}
	while (token[x])
	{
		if (token[x] == '\"' && d_q == true)
			return (true);
		x++;
	}
	return (false);
}


bool	check_s_q(char *token)
{
	int		x;
	bool	s_q;

	x = 0;
	s_q = false;
	if (!token)
		return (false);
	while (token[x])
	{
		if (token[x] == '\'')
		{
			s_q = true;
			x++;
			break ;
		}
		x++;
	}
	while (token[x])
	{
		if (token[x] == '\'' && s_q == true)
			return (true);
		x++;
	}
	return (false);
}

bool	check_quotes(char *token)
{
	int		x;
	bool	q;

	x = 0;
	q = false;
	if (!token)
		return (false);
	while (token[x] && token[x] != '=')
		x++;
	x++;
	if (token[x] == '\"' || token[x] == '\'')
		q = true;
	x++;
	while (token[x] && token[x + 1])
	{
		if ((token[x] == '\"' || token[x] == '\'') && token[x + 1] == '\0'
			&& q == true)
				return (true);
		x++;
	}
	return (false);
}

bool	s_out_q(char *tok)
{
	if (tok[0] == '\'' && tok[ft_strlen(tok) - 1] == '\'')
		return (true);
	else
		return (false);
}