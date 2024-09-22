/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_find_path.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbaumeis <lbaumeis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 13:26:28 by lbaumeis          #+#    #+#             */
/*   Updated: 2024/09/22 17:14:28 by lbaumeis         ###   ########.fr       */
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
	if (t[ft_strlen(t) - 1] == '/')
		new = ft_strjoin_free_one(temp, ft_substr(t, 0, ft_strlen(t) - 1));
	else
		new = ft_strjoin_free_one(temp, t);
	if (!new)
		return (1);
	if (new && is_access(new))
	{
		reset_old_pwd(p, new);
		x = chdir(new);
		return (free(new), new = NULL, x);
	}
	return (free(new), new = NULL, 1);
}

void	check_print(char *s)
{
	int	x;

	x = 0;
	if (ft_strcmp_bool(s, "/"))
		ft_putchar_fd('/', 1);
	while (s[x])
	{
		if (x == 0 && s[x] == '/' && s[x + 1] == '/')
			x++;
		else if (s[x] == '/' && (s[x + 1] == '/' || s[x + 1] == '\0'))
			x++;
		else
		{
			ft_putchar_fd(s[x], 1);
			x++;
		}
	}
	ft_putchar_fd('\n', 1);
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
			check_print(p->pwd);
		x = chdir(temp);
		return (free(temp), temp = NULL, x);
	}
	else if (!is_access(temp))
	{
		reset_old_pwd(p, temp);
		if (print == 1)
			check_print(p->pwd);
		chdir(temp);
		return (free(temp), temp = NULL, 0);
	}
	return (free(temp), temp = NULL, 0);
}

int	go_slash(t_pipex *p, char **token)
{
	if (!p || !token || !token[1])
		return (1);
	if (ft_strcmp_bool(token[1], "/") && is_access(token[1]))
	{
		reset_old_pwd(p, token[1]);
		return (chdir(token[1]));
	}
	return (1);
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
	return (1);
}
