/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_export.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbaumeis <lbaumeis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/03 11:59:53 by lbaumeis          #+#    #+#             */
/*   Updated: 2024/08/10 18:26:42 by lbaumeis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../exec.h"

char	*no_quotes(char *token, int x, int y)
{
	char	*temp;
	
	temp = NULL;
	temp = malloc(sizeof(char) * (y + 1));
	if (!temp)
		return (NULL);
	y = 2;
	x++;
	temp[0] = '=';
	temp[1] = '\"';
	while (token[x])
		temp[y++] = token[x++];
	temp[y] = '\"';
	temp[y + 1] = '\0';
	return (temp);
}

char	*has_quotes(char *token, int x, int y)
{
	char	*temp;
	
	temp = NULL;
	temp = malloc(sizeof(char) * (y + 1));
	if (!temp)
		return (NULL);
	y = 0;
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

char	*modify_quotes(char *token)
{
	int		x;
	int		y;

	x = 0;
	while (token[x] && token[x] != '=')
		x++;
	y = ft_strlen(token) - x;
	if (check_quotes(token) == false)
	{
		y += 2;
		return (no_quotes(token, x, y));
	}
	return (has_quotes(token, x, y));
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
		error(p, "strjoin", p->status);
	x = find_str_part(p->xport, temp);
	free(temp);
	temp = NULL;
	if (x == -1)
		error(p, "couldnt find argument", p->status);
	temp = strcpy_until(p->xport[x]);
	if (!temp)
		error(p, "strcpy_until", p->status);
	temp1 = modify_quotes(token);
	if (!temp1)
		error(p, "modify_quotes", p->status);
	p->xport[x] = ft_strjoin_free_both(temp, temp1);
	if (!p->xport[x])
		error(p, "strjoin_free_both", p->status);
}

void	set_export(t_pipex *p, char **token)
{
	char	*temp;
	int		x;

	temp = NULL;
	x = find_arg(token, "export") + 1;
	if (x == 0)
		error(p, "couldnt find arg", p->status);
	if (token[x][0] == '$')
		error(p, "not a valid identifier", p->status);//not true
	if (valid_env(p, token[x]) == true)
	{
		temp = strcpy_until(token[x]);
		if (!temp)
			error(p, "copy_until", p->status);
		if (find_str_part(p->menv, temp) == -1)
			error(p, "couldnt find arg", p->status);
		else
		{
			p->menv[find_str_part(p->menv, temp)] = ft_strdup(token[x]);
			if (!p->menv[find_str_part(p->menv, temp)])
				error(p, "strdup", p->status);
			update_export(p, temp, token[x]);
		}
	}
	else
		add_to_export(p, token[x]);
}
