/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_export.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbaumeis <lbaumeis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/03 11:59:53 by lbaumeis          #+#    #+#             */
/*   Updated: 2024/08/08 13:27:02 by lbaumeis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "buildins.h"

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

void	update_export(t_buildins *vars, char *tok, char *token)
{
	int		x;
	char	*temp;
	char	*temp1;

	x = 0;
	temp = NULL;
	temp1 = NULL;
	temp = ft_strjoin("declare -x ", tok);
	if (!temp)
		error("strjoin");
	x = find_str_part(vars->xport, temp);
	if (x == -1)
		error("couldnt find argument");
	free(temp);
	temp = NULL;
	temp = strcpy_until(vars->xport[x]);
	if (!temp)
		error("strcpy_until");
	temp1 = modify_quotes(token);
	if (!temp1)
		error("modify_quotes");
	vars->xport[x] = ft_strjoin_free_both(temp, temp1);
	if (!vars->xport[x])
		error("strjoin_free_both");
}

void	set_export(t_buildins *vars, char **token)
{
	char	*temp;
	int		x;

	temp = NULL;
	x = find_arg(token, "export") + 1;
	if (x == 0)
		error("couldnt find arg");
	if (token[x][0] == '$')
		error("not a valid identifier");//not true
	if (valid_env(vars, token[x]) == true)
	{
		temp = strcpy_until(token[x]);
		if (!temp)
			error("copy_until");
		if (find_str_part(vars->menv, temp) == -1)
			error("couldnt find arg");
		else
		{
			vars->menv[find_str_part(vars->menv, temp)] = ft_strdup(token[x]);
			if (!vars->menv[find_str_part(vars->menv, temp)])
				error("strdup");
			update_export(vars, temp, token[x]);
		}
	}
	else
		add_to_export(vars, token[x]);
}
