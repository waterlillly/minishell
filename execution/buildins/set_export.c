/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_export.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbaumeis <lbaumeis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/03 11:59:53 by lbaumeis          #+#    #+#             */
/*   Updated: 2024/08/04 13:26:25 by lbaumeis         ###   ########.fr       */
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
		{
			temp[y] = '\"';
			y++;
			x++;
		}
		else
			temp[y++] = token[x++];
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
		err_or("strjoin");
	x = find_str_part(vars->export, temp);
	if (x == -1)
		err_or("couldnt find argument");
	free(temp);
	temp = NULL;
	temp = strcpy_until(vars->export[x]);
	if (!temp)
		err_or("strcpy_until");
	temp1 = modify_quotes(token);
	if (!temp1)
		err_or("modify_quotes");
	vars->export[x] = ft_strjoin_free_both(temp, temp1);
	if (!vars->export[x])
		err_or("strjoin_free_both");
}

void	set_export(t_buildins *vars, char **token)
{
	int		x;
	char	*temp;

	temp = NULL;
	x = find_arg(token, "export") + 1;
	if (x == 0)
		err_or("couldnt find arg");
	if (token[x][0] == '$')
		err_or("not a valid identifier");
	if (valid_env(vars, token[x]) == true)
	{
		temp = strcpy_until(token[x]);
		if (!temp)
			err_or("copy_until");
		if (find_str_part(vars->menv, temp) == -1)
			err_or("couldnt find env");
		else
		{
			vars->menv[find_str_part(vars->menv, temp)] = ft_strdup(token[x]);
			if (!vars->menv[find_str_part(vars->menv, temp)])
				err_or("strdup");
			update_export(vars, temp, token[x]);
		}
	}
}
