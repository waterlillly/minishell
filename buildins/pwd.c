/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbaumeis <lbaumeis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/27 12:47:48 by lbaumeis          #+#    #+#             */
/*   Updated: 2024/09/22 17:20:57 by lbaumeis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	reset_old_pwd(t_pipex *p, char *path)
{
	char	*temp;

	temp = NULL;
	temp = ft_strdup(p->oldpwd);
	if (!temp)
		return ;
	free(p->oldpwd);
	p->oldpwd = NULL;
	p->oldpwd = ft_strdup(p->pwd);
	if (!p->oldpwd)
		return ;
	free(p->pwd);
	p->pwd = NULL;
	p->pwd = ft_strdup(path);
	if (!p->pwd)
		p->pwd = ft_strdup(temp);
	free(temp);
	temp = NULL;
}

int	get_int(char **temp)
{
	int	x;
	int	i;

	x = 0;
	i = 0;
	while (temp[x])
	{
		if (ft_strcmp_bool(temp[x], ".."))
			i++;
		x++;
	}
	return (i);
}

int	going_back(char *oldpwd, t_pipex *p, int y, char **temp)
{
	int	x;
	int	z;

	x = 0;
	z = ft_arrlen(temp) - 1;
	while (p && temp[x] && x < (z - (y * 2)))
	{
		if (oldpwd[ft_strlen(oldpwd) - 1] != '/')
			oldpwd = ft_strjoin_free_one(oldpwd, "/");
		oldpwd = ft_strjoin_free_both(oldpwd, temp[x]);
		x++;
	}
	if (x == (z - (y * 2)) && is_access(oldpwd))
		return (p->oldpwd = NULL, p->oldpwd = oldpwd, update(p, "OLDPWD", p->pwd),
			update(p, "PWD", p->oldpwd), 0);
	while (temp[x])
	{
		if (oldpwd[ft_strlen(oldpwd) - 1] != '/')
			oldpwd = ft_strjoin_free_one(oldpwd, "/");
		oldpwd = ft_strjoin_free_both(oldpwd, temp[x]);
		x++;
	}
	oldpwd = ft_strjoin_free_one(oldpwd, "/..");
	return (p->oldpwd = NULL, p->oldpwd = oldpwd, update(p, "OLDPWD", p->pwd),
		update(p, "PWD", p->oldpwd), 0);
}

/*
/home/lbaumeis/CCore/projects/minishell> mkdir a
/home/lbaumeis/CCore/projects/minishell> cd a
/home/lbaumeis/CCore/projects/minishell/a> mkdir b
/home/lbaumeis/CCore/projects/minishell/a> cd b
/home/lbaumeis/CCore/projects/minishell/a/b> mkdir c
/home/lbaumeis/CCore/projects/minishell/a/b> cd c
/home/lbaumeis/CCore/projects/minishell/a/b/c> rm -r ../../../a
/home/lbaumeis/CCore/projects/minishell/a/b/c> cd ..
/home/lbaumeis/CCore/projects/minishell/a/b/c: No such file or directory
/home/lbaumeis/CCore/projects/minishell/a/b/c/..> echo $PWD $OLDPWD
-->/home/lbaumeis/CCore/projects/minishell/a/b/c/.. /home/lbaumeis/CCore/projects/minishell/a/b/c/..
/home/lbaumeis/CCore/projects/minishell/a/b/c/..> cd ..
/home/lbaumeis/CCore/projects/minishell/a/b/c/../..> echo $PWD $OLDPWD
-->/home/lbaumeis/CCore/projects/minishell/a/b/c/../.. /home/lbaumeis/CCore/projects/minishell/a/b/c/../..
/home/lbaumeis/CCore/projects/minishell/a/b/c/../..> cd ..
/home/lbaumeis/CCore/projects/minishell> echo $PWD $OLDPWD
/home/lbaumeis/CCore/projects/minishell /home/lbaumeis/CCore/projects/minishell
/home/lbaumeis/CCore/projects/minishell> pwd
/home/lbaumeis/CCore/projects/minishell
/home/lbaumeis/CCore/projects/minishell> cd -
/home/lbaumeis/CCore/projects/minishell/a/b/c/../..
-->/home/lbaumeis/CCore/projects/minishell/a/b/c/../..> pwd
/home/lbaumeis/CCore/projects/minishell
-->/home/lbaumeis/CCore/projects/minishell/a/b/c/../..> mkdir xxx (works, shouldnt)
/home/lbaumeis/CCore/projects/minishell/a/b/c/../..> 
*/

int	join_oldpwd(t_pipex *p, char **temp, char *oldpwd)
{
	int	x;
	int	y;
	int	z;

	x = 0;
	y = get_int(temp);
	z = ft_arrlen(temp) - 1;
	if (p && temp[x] && y > 0)
		return (going_back(oldpwd, p, y, temp));
	while (p && temp[x])
	{
		if (!temp[x + 1])
		{
			oldpwd = ft_strjoin_free_one(oldpwd, "/");
			oldpwd = ft_strjoin_free_one(oldpwd, temp[x]);
			if (!is_access(oldpwd))
			{
				oldpwd = ft_strjoin_free_one(oldpwd, "/..");
				return (p->oldpwd = NULL, p->oldpwd = oldpwd, update(p, "OLDPWD", p->pwd),
					update(p, "PWD", p->oldpwd), 0);
			}
			return (p->oldpwd = NULL, p->oldpwd = oldpwd, update(p, "OLDPWD", p->pwd),
				update(p, "PWD", p->oldpwd), 0);
		}
		if (oldpwd[ft_strlen(oldpwd) - 1] != '/')
			oldpwd = ft_strjoin_free_one(oldpwd, "/");
		oldpwd = ft_strjoin_free_both(oldpwd, temp[x]);
		x++;
	}
	return (0);
}

int	go_up_oldpwd(t_pipex *p)
{
	char	**temp;
	char	*oldpwd;

	temp = NULL;
	oldpwd = NULL;
	if (!p)
		return (1);
	if (!p->pwd)
	{
		p->pwd = NULL;
		p->pwd = get_env(p, "PWD");
		if (!p->pwd)
			return (1);
	}
	if (ft_strcmp_bool(p->pwd, "/"))
		return (0);
	temp = ft_split(p->pwd, '/');
	if (!temp)
		return (1);
	oldpwd = ft_strdup("");
	if (!oldpwd)
		return (1);
	return (join_oldpwd(p, temp, oldpwd));
}
