/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_export.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbaumeis <lbaumeis@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/03 11:59:53 by lbaumeis          #+#    #+#             */
/*   Updated: 2024/08/18 17:43:22 by lbaumeis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
/*
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
			temp[y] = '\"';
		else
			temp[y] = token[x];
		x++;
		y++;
	}
	temp[y] = '\0';
	return (temp);
}
*/

void	update_export(t_pipex *p, char *tok, char *token)
{
	int		x;
	char	*temp;
	char	*temp1;

	x = 0;
	temp = NULL;
	temp1 = NULL;
	if (!p || !tok || !token)
		return ;
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

	temp = NULL;
	if (!p || !token || !ft_strcmp_bool(token[0], "export") || !token[1])
		return ;
	if (token[1][0] == '$')
		return ;//error(p, "not a valid identifier", p->status);
	temp = strcpy_until(token[1]);
	if (!temp)
		return ;//error(p, "copy_until", p->status);
	if (valid_env(p, temp) == true)
	{
		if (ft_strchr(remove_quotes(token[1]), '='))
			p->menv[find_str_part(p->menv, temp)] = remove_quotes(token[1]);
		update_export(p, temp, remove_quotes(token[1]));
	}
	else
		add_to_export(p, remove_quotes(token[1]));
	free(temp);
	temp = NULL;
}

void	update(t_pipex *p, char *set, char *tok)
{
	char	*temp;
	int		x;

	temp = NULL;
	x = 0;
	if (!p || !p->menv || !p->xport || !tok || !is_access(tok))
		return ;
	x = find_str_part(p->menv, set);
	if (x < 0)
		return ;
	temp = ft_strjoin(set, "=");
	if (!temp)
		return ;
	p->menv[x] = NULL;
	p->menv[x] = ft_strjoin_free_one(temp, tok);
	if (!p->menv[x])
		return ;
	update_export(p, set, tok);
}
