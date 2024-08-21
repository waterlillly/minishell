/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_find_path.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbaumeis <lbaumeis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 13:26:28 by lbaumeis          #+#    #+#             */
/*   Updated: 2024/08/21 15:52:34 by lbaumeis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	add_to_path(t_pipex *p, char *t)
{
	char	*temp;
	char	*new;
	int		x;

	temp = NULL;
	new = NULL;
	x = 0;
	if (!p || !t)
		return (1);
	temp = ft_strjoin(p->pwd, "/");
	if (!temp)
		return (1);
	new = ft_strjoin_free_one(temp, t);
	if (!new)
		return (1);
	if (new && is_access(new))
	{
		reset_old_pwd(p, new);
		x = chdir(new);
		//if (x == 0)
		//	update_both(p);
		return (x);
	}
	return (1);
}

int	go_back(t_pipex *p, int print)
{
	char	*temp;
	int		x;

	temp = NULL;
	x = 0;
	if (!p)
		return (1);
	temp = ft_strdup(p->oldpwd);
	if (!temp)
		return (1);
	if (is_access(temp))
	{
		reset_old_pwd(p, temp);
		if (print == 1)
			printf("%s\n", p->pwd);
		x = chdir(temp);
		//if (x == 0)
		//	update_both(p);
		return (x);
	}
	return (0);
}

char	*check_slash(char *tok, char *temp)
{
	int	x;

	x = 0;
	if (!tok || !temp)
		return (NULL);
	while (tok[x])
	{
		if (tok[x] == '/')
			x++;
		else
			return (NULL);
	}
	if (x > 2)
	{
		temp = ft_strdup("/");
		if (!temp)
			return (NULL);
		return (temp);
	}
	else
		return (tok);
}

int	go_slash(t_pipex *p, char **token)
{
	char	*temp;
	int		x;

	temp = NULL;
	x = 0;
	if (!p || !token || !token[1])
		return (1);
	if ((token[1][1] == '/' && token[1][2] == '\0')
		|| (token[1][1] == '\0'
		|| (token[1][1] == '/' && token[1][2] == '/')))
	{
		temp = check_slash(token[1], temp);
		if (!temp)
			return (1);
		if (is_access(temp))
		{
			reset_old_pwd(p, temp);
			x = chdir(token[1]);
			//if (x == 0)
			//	update_both(p);
			return (x);
		}
	}
	return (1);
}

int	go_full_path(t_pipex *p, char **token)
{
	int	x;

	x = 0;
	if (!p || !token || !token[1])
		return (1);
	if (is_access(token[1]))
	{
		reset_old_pwd(p, token[1]);
		x = chdir(token[1]);
		//if (x == 0)
		//	x = update_both(p);
		return (x);
	}
	return (1);
}
