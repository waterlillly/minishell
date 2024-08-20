/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_find_path.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbaumeis <lbaumeis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 13:26:28 by lbaumeis          #+#    #+#             */
/*   Updated: 2024/08/20 20:01:21 by lbaumeis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	add_to_path(t_pipex *p, char *t)
{
	char	*temp;
	char	*new;

	temp = NULL;
	new = NULL;
	if (!p || !t)
		return (1);
	temp = ft_strjoin(p->pwd, "/");//
	if (!temp)
		return (1);//error(p, temp, p->status);
	new = ft_strjoin_free_one(temp, t);
	if (!new)
		return (1);//error(p, temp, p->status);
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
	if (!p)
		return (1);
	temp = ft_strdup(p->oldpwd);
	if (!temp)
		return (1);//error(p, temp, p->status);
	if (is_access(temp))
	{
		reset_old_pwd(p, temp);
		if (print == 1)
			printf("%s\n", p->pwd);
		return (chdir(temp));
	}
	return (0);//error(p, temp, p->status)
}

char	*check_slash(char *tok, char *temp)//t_pipex *p, 
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

int	go_slash(t_pipex *p, char **token)
{
	char	*temp;

	temp = NULL;
	if (!p || !token || !token[1])
		return (1);
	if ((token[1][1] == '/' && token[1][2] == '\0')
		|| (token[1][1] == '\0'
		|| (token[1][1] == '/' && token[1][2] == '/')))
	{
		temp = check_slash(token[1], temp);//p, 
		if (!temp)
			return (1);//error(p, temp, p->status);
		if (is_access(temp))
		{
			reset_old_pwd(p, temp);
			return (chdir(token[1]));
		}
	}
	return (1);//error(p, token[1], p->status)
}

int	go_full_path(t_pipex *p, char **token)
{
	if (!p || !token || !token[1])
		return (1);
	if (is_access(token[1]))
	{
		reset_old_pwd(p, token[1]);
		return (chdir(token[1]));
	}
	return (1);//error(p, token[1], p->status)
}
