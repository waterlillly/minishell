/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_find_path.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbaumeis <lbaumeis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 13:26:28 by lbaumeis          #+#    #+#             */
/*   Updated: 2024/08/07 14:03:43 by lbaumeis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	add_to_path(t_ms *ms, char *t)
{
	char	*temp;
	char	*new;

	temp = NULL;
	new = NULL;
	temp = ft_strjoin(ms->e->pwd, "/");
	if (!temp)
		error(ms, temp, 1);
	new = ft_strjoin_free_one(temp, t);
	if (!new)
		error(ms, temp, 1);
	if (access(new, X_OK) == 0)
		error(ms, "access", 1);
	if (new && is_access(new))
	{
		reset_old_pwd(ms, new);
		return (chdir(new));
	}
	return (error(ms, new, 1));
}

int	go_back(t_ms *ms, int print)
{
	char	*temp;

	temp = NULL;
	temp = ft_strdup(ms->e->oldpwd);
	if (!temp)
		error(ms, temp, 1);
	if (is_access(temp))
	{
		reset_old_pwd(ms, temp);
		if (print == 1)
			printf("%s\n", ms->e->oldpwd);
		return (chdir(temp));
	}
	return (error(ms, temp, 1));
}

char	*check_slash(t_ms *ms, char *tok, char *temp)
{
	int	x;

	x = 0;
	while (tok[x])
	{
		if (tok[x] == '/')
			x++;
		else
			return (error(ms, "no such file or directory", 1), NULL);
	}
	if (x > 2)
	{
		temp = ft_strdup("/");
		if (!temp)
			error(ms, temp, 1);
		return (temp);
	}
	else
		return (tok);
}

int	go_slash(t_ms *ms, char **token, int x)
{
	char	*temp;

	temp = NULL;
	if ((token[x + 1][1] == '/' && token[x + 1][2] == '\0')
		|| (token[x + 1][1] == '\0'
		|| (token[x + 1][1] == '/' && token[x + 1][2] == '/')))
	{
		temp = check_slash(ms, token[x + 1], temp);
		if (!temp)
			error(ms, temp, 1);
		if (is_access(temp))
		{
			reset_old_pwd(ms, temp);
			return (chdir(token[x + 1]));
		}
	}
	return (error(ms, token[x + 1], 1));
}

int	go_full_path(t_ms *ms, char **token, int x)
{
	if (is_access(token[x + 1]) == true)
	{
		reset_old_pwd(ms, token[x + 1]);
		return (chdir(token[x + 1]));
	}
	return (error(ms, token[x + 1], 1));
}
