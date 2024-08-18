/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbaumeis <lbaumeis@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/18 16:24:45 by lbaumeis          #+#    #+#             */
/*   Updated: 2024/08/18 16:49:39 by lbaumeis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*add_quotes(char *token)
{
	int		x;
	int		y;
	char	*new;

	x = 0;
	new = NULL;
	if (!token)
		return (NULL);
	while (token[x] && token[x] != '=')
		x++;
	new = malloc(sizeof(char) * (ft_strlen(token) - x + 3));
	if (!new)
		return (NULL);
	x++;
	y = 2;
	new[0] = '=';
	new[1] = '\"';
	while (token[x])
		new[y++] = token[x++];
	new[y] = '\"';
	new[y + 1] = '\0';
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
	temp = malloc(sizeof(char) * (ft_strlen(s) - 1));
	if (!temp)
		return (NULL);
	while (s[x])
	{
		if (s[x] == '\"' || s[x] == '\'')
			x++;
		else
		{
			temp[y] = s[x];
			y++;
			x++;
		}
	}
	temp[y] = '\0';
	return (temp);
}

bool	check_quotes(char *token)////redo each quote
{
	int		x;
	bool	q1;

	x = 0;
	q1 = false;
	if (!token)
		return (false);
	while (token[x] && token[x] != '=')
		x++;
	x++;
	if (token[x] == '\"' || token[x] == '\'')
		q1 = true;
	x++;
	while (token[x] && token[x + 1])
	{
		if ((token[x] == '\"' || token[x] == '\'') && token[x + 1] == '\0'
			&& q1 == true)
				return (true);
		x++;
	}
	return (false);
}

