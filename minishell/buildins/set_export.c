/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_export.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbaumeis <lbaumeis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/03 11:59:53 by lbaumeis          #+#    #+#             */
/*   Updated: 2024/08/07 14:08:26 by lbaumeis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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

void	update_export(t_ms *ms, char *tok, char *token)
{
	int		x;
	char	*temp;
	char	*temp1;

	x = 0;
	temp = NULL;
	temp1 = NULL;
	temp = ft_strjoin("declare -x ", tok);
	if (!temp)
		error(ms, "strjoin", 1);
	x = find_str_part(ms->e->xport, temp);
	if (x == -1)
		error(ms, "couldnt find argument", 1);
	free(temp);
	temp = NULL;
	temp = strcpy_until(ms->e->xport[x]);
	if (!temp)
		error(ms, "strcpy_until", 1);
	temp1 = modify_quotes(token);
	if (!temp1)
		error(ms, "modify_quotes", 1);
	ms->e->xport[x] = ft_strjoin_free_both(temp, temp1);
	if (!ms->e->xport[x])
		error(ms, "strjoin_free_both", 1);
}

void	set_export(t_ms *ms, char **token)
{
	char	*temp;
	int		x;

	temp = NULL;
	x = find_arg(token, "export") + 1;
	if (x == 0)
		error(ms, "couldnt find arg", 1);
	//if (token[x][0] == '$')
	//	err_or("not a valid identifier");//not true
	if (valid_env(ms, token[x]) == true)
	{
		temp = strcpy_until(token[x]);
		if (!temp)
			error(ms, "copy_until", 1);
		if (find_str_part(ms->e->menv, temp) == -1)
			error(ms, "couldnt find arg", 1);
		else
		{
			ms->e->menv[find_str_part(ms->e->menv, temp)] = ft_strdup(token[x]);
			if (!ms->e->menv[find_str_part(ms->e->menv, temp)])
				error(ms, "strdup", 1);
			update_export(ms, temp, token[x]);
		}
	}
	else
		add_to_export(ms, token[x]);
}
