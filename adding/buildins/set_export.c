/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_export.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbaumeis <lbaumeis@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/03 11:59:53 by lbaumeis          #+#    #+#             */
/*   Updated: 2024/08/14 14:35:29 by lbaumeis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*no_quotes(char *token, int x, int y)
{
	char	*temp;
	
	temp = NULL;
	if (!token || !token[x] || y <= 1)
		return (NULL);
	temp = malloc(sizeof(char) * (y + 1));
	if (!temp)
		return (NULL);
	x++;
	y = 2;
	temp[0] = '=';
	temp[1] = '\"';
	while (token[x])
	{
		temp[y] = token[x];
		y++;
		x++;
	}
	temp[y] = '\"';
	temp[y + 1] = '\0';
	return (temp);
}

char	*has_quotes(char *token, int x, int y)
{
	char	*temp;
	
	temp = NULL;
	if (!token || !token[x] || y <= 1)
		return (NULL);
	temp = malloc(sizeof(char) * (y + 1));
	if (!temp)
		return (NULL);
	y = 0;
	x++;
	while (token[x])
	{
		if (y == 1 || x == (int)ft_strlen(token) - 1)
		{
			ft_putstr_fd("token[x]: ", token[x]);
			temp[y] = '\"';
			ft_putstr_fd("temp[y]: ", temp[y]);
		}
		else
		{
			ft_putstr_fd("token[x]: ", token[x]);
			temp[y] = token[x];
			ft_putstr_fd("temp[y]: ", temp[y]);
		}
		x++;
		y++;
	}
	temp[y] = '\0';
	return (temp);
}

char	*add_quotes(char *token)
{
	int		x;
	int		y;
	char	*new;

	x = 0;
	new = NULL;
	while (token[x] && token[x] != '=')
		x++;
	y = ft_strlen(token) - x;
	new = malloc(sizeof(char) * (y + 3));
	if (!new)
		return (NULL);
	x++;
	y = 2;
	new[0] = '=';
	new[1] = '\"';
	while (token[x])
	{
		new[y] = token[x];
		y++;
		x++;
	}
	new[y] = '\"';
	new[y + 1] = '\0';
	return (new);
}

void	update_export(t_pipex *p, char *tok, char *token)
{
	int		x;
	char	*temp;
	char	*temp1;

	x = 0;
	temp = NULL;
	temp1 = NULL;
	temp = ft_strjoin("declare -x ", tok);
	if (!temp)
		return ;//error(p, "strjoin", p->status);
	x = find_str_part(p->xport, temp);
	if (x == -1)
		return ;//error(p, "couldnt find argument", p->status);
	temp1 = add_quotes(token);
	if (!temp1)
		return ;//error(p, "modify_quotes", p->status);
	p->xport[x] = ft_strjoin_free_both(temp, temp1);
	if (!p->xport[x])
		return ;//error(p, "strjoin_free_both", p->status);
}

void	set_export(t_pipex *p, char **token)
{
	char	*temp;
	char	*toknoquo;
	int		x;

	temp = NULL;
	toknoquo = NULL;
	x = 1;
	if (token[x][0] == '$')
		return ;//error(p, "not a valid identifier", p->status);
	toknoquo = remove_quotes(token[x]);
	temp = strcpy_until(token[x]);
	if (!temp)
		return ;//error(p, "copy_until", p->status);
	if (valid_env(p, temp) == true)
	{
		if (ft_strchr(toknoquo, '='))
			p->menv[find_str_part(p->menv, temp)] = toknoquo;
		update_export(p, temp, toknoquo);
	}
	else
		add_to_export(p, toknoquo);
}
