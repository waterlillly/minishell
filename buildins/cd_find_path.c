/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_find_path.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbaumeis <lbaumeis@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 13:26:28 by lbaumeis          #+#    #+#             */
/*   Updated: 2024/08/14 14:35:12 by lbaumeis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	add_to_path(t_pipex *p, char *t)
{
	char	*temp;
	char	*new;

	temp = NULL;
	new = NULL;
	temp = ft_strjoin(p->pwd, "/");
	if (!temp)
		return (1);//error(p, temp, p->status);
	new = ft_strjoin_free_one(temp, t);
	if (!new)
		return (1);//error(p, temp, p->status);
	if (access(new, X_OK) == 0)
		return (1);//error(p, "access", p->status)
	if (new && is_access(new))
	{
		reset_old_pwd(p, new);
		return (chdir(new));
	}
	return (1);//error(p, new, p->status)
}

int	go_back(t_pipex *p, int print)
{
	char	*temp;

	temp = NULL;
	temp = ft_strdup(p->oldpwd);
	if (!temp)
		return (1);//error(p, temp, p->status);
	if (is_access(temp))
	{
		reset_old_pwd(p, temp);
		if (print == 1)
			printf("%s\n", p->oldpwd);
		return (chdir(temp));
	}
	return (1);//error(p, temp, p->status)
}

char	*check_slash(char *tok, char *temp)//t_pipex *p, 
{
	int	x;

	x = 0;
	while (tok[x])
	{
		if (tok[x] == '/')
			x++;
		else
			return (NULL);//error(p, "no such file or directory", p->status)
	}
	if (x > 2)
	{
		temp = ft_strdup("/");
		if (!temp)
			return (NULL);//error(p, temp, p->status);
		return (temp);
	}
	else
		return (tok);
}

int	go_slash(t_pipex *p, char **token, int x)
{
	char	*temp;

	temp = NULL;
	if ((token[x + 1][1] == '/' && token[x + 1][2] == '\0')
		|| (token[x + 1][1] == '\0'
		|| (token[x + 1][1] == '/' && token[x + 1][2] == '/')))
	{
		temp = check_slash(token[x + 1], temp);//p, 
		if (!temp)
			return (1);//error(p, temp, p->status);
		if (is_access(temp))
		{
			reset_old_pwd(p, temp);
			return (chdir(token[x + 1]));
		}
	}
	return (1);//error(p, token[x + 1], p->status)
}

int	go_full_path(t_pipex *p, char **token, int x)
{
	if (is_access(token[x + 1]) == true)
	{
		reset_old_pwd(p, token[x + 1]);
		return (chdir(token[x + 1]));
	}
	return (1);//error(p, token[x + 1], p->status)
}
