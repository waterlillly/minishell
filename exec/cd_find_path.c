// /* ************************************************************************** */
// /*                                                                            */
// /*                                                        :::      ::::::::   */
// /*   cd_find_path.c                                     :+:      :+:    :+:   */
// /*                                                    +:+ +:+         +:+     */
// /*   By: lbaumeis <lbaumeis@student.42.fr>          +#+  +:+       +#+        */
// /*                                                +#+#+#+#+#+   +#+           */
// /*   Created: 2024/07/30 13:26:28 by lbaumeis          #+#    #+#             */
// /*   Updated: 2024/10/06 13:21:07 by lbaumeis         ###   ########.fr       */
// /*                                                                            */
// /* ************************************************************************** */

// #include "../minishell.h"

// int	add_to_path(t_pipex *p, char *t)
// {
// 	char	*temp;
// 	char	*new;
// 	int		x;

// 	temp = NULL;
// 	new = NULL;
// 	x = 0;
// 	if (!p || !t)
// 		return (1);
// 	if (!ft_strcmp_bool(p->pwd, "/"))
// 		temp = ft_strjoin(p->pwd, "/");
// 	else
// 		temp = ft_strdup(p->pwd);
// 	if (!temp)
// 		return (1);
// 	if (t[ft_strlen(t) - 1] == '/')
// 		new = ft_strjoin_free_both(temp, ft_substr(t, 0, ft_strlen(t) - 1));
// 	else
// 		new = ft_strjoin_free_one(temp, t);
// 	if (!new)
// 		return (1);
// 	if (new && is_access(new))
// 	{
// 		x = chdir(new);
// 		if (x == 0)
// 			reset_old_pwd(p, new);
// 		return (free(new), new = NULL, x);
// 	}
// 	return (free(new), new = NULL, 1);
// }

// void	check_print(char *s)
// {
// 	int	x;

// 	x = 0;
// 	if (ft_strcmp_bool(s, "/"))
// 		ft_putchar_fd('/', 1);
// 	while (s[x])
// 	{
// 		if (x == 0 && s[x] == '/' && s[x + 1] == '/')
// 			x++;
// 		else if (s[x] == '/' && (s[x + 1] == '/' || s[x + 1] == '\0'))
// 			x++;
// 		else
// 		{
// 			ft_putchar_fd(s[x], 1);
// 			x++;
// 		}
// 	}
// 	ft_putchar_fd('\n', 1);
// }

// int	go_back(t_pipex *p, int print)
// {
// 	char	*temp;
// 	int		x;

// 	temp = NULL;
// 	x = 0;
// 	if (!p)
// 		return (1);
// 	temp = ft_strdup(p->oldpwd);
// 	if (!temp)
// 		return (1);
// 	if (is_access(temp))
// 	{
// 		reset_old_pwd(p, temp);
// 		if (print == 1)
// 			check_print(p->pwd);
// 		x = chdir(p->pwd);
// 		return (free(temp), temp = NULL, x);
// 	}
// 	else if (temp[ft_strlen(temp) - 1] != '.' && temp[ft_strlen(temp) - 2] != '.')
// 	{
// 		reset_old_pwd(p, temp);
// 		if (print == 1)
// 			check_print(p->pwd);
// 		chdir(temp);
// 		return (free(temp), temp = NULL, 0);
// 	}
// 	return (chdir(temp), free(temp), temp = NULL, 0);
// }

// int	go_slash(t_pipex *p, char **token)
// {
// 	int		x;

// 	x = 0;
// 	if (!p || !token || !token[1])
// 		return (1);
// 	if (is_access(token[1]) && (ft_strcmp_bool(token[1], "/") || ft_strcmp_bool(token[1], "//")))
// 	{
// 		reset_old_pwd(p, token[1]);
// 		return (chdir(token[1]));
// 	}
// 	else if (token[1][0] == '/' && token[1][1] != '\0')
// 	{
// 		while (token[1][x])
// 		{
// 			if (token[1][x] == '/')
// 				x++;
// 			else
// 				return (1);
// 		}
// 		reset_old_pwd(p, "/");
// 		return (chdir("/"));
// 	}
// 	return (1);
// }

// int	go_full_path(t_pipex *p, char **token)
// {
// 	if (!p || !token || !token[1])
// 		return (1);
// 	if (is_access(token[1]))
// 	{
// 		reset_old_pwd(p, token[1]);
// 		return (chdir(token[1]));
// 	}
// 	return (1);
// }
