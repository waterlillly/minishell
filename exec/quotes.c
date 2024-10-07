/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbaumeis <lbaumeis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/18 16:24:45 by lbaumeis          #+#    #+#             */
/*   Updated: 2024/10/05 17:52:35 by lbaumeis         ###   ########.fr       */
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
	free(token);
	return (new);
}

char	*remove_quotes(char *s)
{
	int		x;
	int		y;
	int		q;
	char	*temp;

	x = 0;
	y = 0;
	temp = NULL;
	if (!s || ft_strlen(s) < 3)
		return (NULL);
	else if (!check_d_q(s) && !check_s_q(s))
		return (s);
	q = 0;
	while (*s)
	{
		if (*s == '\'' || *s == '\"')
			q++;
		s++;
	}
	temp = ft_calloc((ft_strlen(s) - q + 1), sizeof(char));
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

int	check_d_q(char *token)
{
	int	x;
	int	d_q;

	x = 0;
	d_q = 0;
	if (!token)
		return (false);
	while (token[x])
	{
		if (token[x] == '\"')
			d_q++;
		x++;
	}
	return (d_q);
}

bool	check_s_q(char *token)
{
	int	x;
	int	s_q;

	x = 0;
	s_q = 0;
	if (!token)
		return (false);
	while (token[x])
	{
		if (token[x] == '\'')
			s_q++;
		x++;
	}
	if (s_q != 0 && s_q % 2 == 0)
		return (true);
	return (false);
}

bool	s_out_q(char *tok)
{
	if (tok[0] == '\'' && tok[ft_strlen(tok) - 1] == '\'')
		return (true);
	else
		return (false);
}

bool	d_out_q(char *tok)
{
	if (tok[0] == '\"' && tok[ft_strlen(tok) - 1] == '\"')
		return (true);
	else
		return (false);
}

bool	only_quotes(char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == '\'' || s[i] == '\"')
			i++;
		else
			return (false);
	}
	return (true);
}

int	only_q(char *s, int q)
{
	int	i;

	i = 0;
	while (s[i] && s[i] == q)
	{
		i++;
		if (s[i] == '\0')
			return (i);	
	}
	return (-1);
}

int	count_q(char *s, int q)
{
	int	i;
	int	c;

	i = 0;
	c = 0;
	while (s[i])
	{
		if (s[i] == q)
			c++;
		i++;
	}
	return (c);
}
