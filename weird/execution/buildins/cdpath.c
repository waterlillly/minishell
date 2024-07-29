/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cdpath.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbaumeis <lbaumeis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/28 11:38:34 by lbaumeis          #+#    #+#             */
/*   Updated: 2024/07/29 17:01:44 by lbaumeis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "buildins.h"

/*
cd (no options) -> if $HOME is empty or undefined = handle differently!
else: go to home dir
if cd + /"smth" -> change cur dir to that dir (if it exists)

->	Starting with the  first  pathname  in  the
	<colon>-separated  pathnames of CDPATH (see
	the ENVIRONMENT VARIABLES section)  if  the
	pathname  is non-null, test if the concate‐
	nation of that pathname, a <slash>  charac‐
	ter  if  that  pathname  did not end with a
	<slash> character, and the directory  oper‐
	and  names  a directory. If the pathname is
	null, test if the concatenation of  dot,  a
	<slash>  character, and the operand names a
	directory. In either case, if the resulting
	string  names  an  existing  directory, set
	curpath to that string and proceed to  step
	7.  Otherwise,  repeat  this  step with the
	next pathname in CDPATH until all pathnames
	have been tested.

->	If  curpath is longer than {PATH_MAX} bytes
	(including the terminating  null)  and  the
	directory   operand  was  not  longer  than
	{PATH_MAX} bytes (including the terminating
	null), then curpath shall be converted from
	an absolute pathname to an equivalent rela‐
	tive  pathname if possible. This conversion
	shall always be considered possible if  the
	value of PWD, with a trailing <slash> added
	if it does not already have one, is an ini‐
	tial  substring of curpath.  Whether or not
	it is considered possible under other  cir‐
	cumstances  is unspecified. Implementations
	may also apply this conversion  if  curpath
	is  not longer than {PATH_MAX} bytes or the
	directory   operand   was    longer    than
	{PATH_MAX} bytes.

->	The  cd  utility shall then perform actions
	equivalent to the chdir()  function  called
	with curpath as the path argument. If these
	actions fail for any reason, the cd utility
	shall  display an appropriate error message
	and the remainder of this step shall not be
	executed.  If  the  -P option is not in ef‐
	fect, the PWD environment variable shall be
	set  to the value that curpath had on entry
	to step 9 (i.e.,  before  conversion  to  a
	relative  pathname). If the -P option is in
	effect, the PWD environment variable  shall
	be  set  to the string that would be output
	by pwd -P.  If there is  insufficient  per‐
	mission  on  the  new  directory, or on any
	parent of that directory, to determine  the
	current working directory, the value of the
	PWD environment variable is unspecified.

->	If, during the execution of  the  above  steps,
	the PWD environment variable is set, the OLDPWD
	environment variable shall also be set  to  the
	value of the old working directory (that is the
	current working directory immediately prior  to
	the call to cd).

-> make temp of oldpwd
-> if cddir is successful set oldpwd to pwd and pwd to new dir (+delete temp)
-> else: keep temp as oldpwd

-> cddir success: return (0)
	else: return >0

*/

int	cd_home(t_buildins *vars)
{
	if (!vars->home)
		get_home(vars);
	if (ft_strcmp(vars->home, vars->pwd))
		return (0);
	reset_old_pwd(vars, vars->home);
	return (chdir("~"));
}

/*
cd + / -> pwd = / (also if cd + /// and ////)
cd + // -> pwd = //
(/ and // display the same with ls)
cd + ~ or cd + nothing or cd + . -> pwd = /home/lbaumeis
cd + .. -> pwd = /home
(add check for going way back-> needs to stay in the last one found --> should be /)
cd + ~~ -> no such file or directory
*/

int	cd_path(t_buildins *vars, char *path)
{
	if (path != NULL)
	{
		if (ft_strcmp(path, vars->pwd))
			return (0);
		if (access(path, F_OK) && chdir(path) == 0)
		{
			reset_old_pwd(vars, path);
			return (0);
		}
		else if (access(path, F_OK) == -1 || chdir(path) != 0)
		{
			perror(path);
			return (1);
		}
	}
	return (1);
}
char	*add_to_path(t_buildins *vars, char *t)
{
	char	*temp;
	char	*new;

	temp = NULL;
	new = NULL;
	temp = ft_strjoin(vars->pwd, "/");
	if (!temp)
		return (NULL);
	new = ft_strjoin_free_one(temp, t);
	if (!new)
		return (NULL);
	//if (access(new, F_OK) == -1)
		//return (ft_putendl_fd("No such file or directory", 2), NULL);
	//if (new && access(new, F_OK) == 0)
		//reset_old_pwd(vars, new);
	return (new);
}

char	*go_up(t_buildins *vars, char *temp)//add check if already at start
{
	go_up_oldpwd(vars);
	temp = ft_strdup(vars->oldpwd);
	if (!temp)
		return (NULL);
	if (access(temp, F_OK) && chdir(temp) == 0)
		reset_old_pwd(vars, temp);
	return (free(temp), temp = NULL, NULL);
}

char	*go_back(t_buildins *vars, char *temp)
{
	temp = ft_strdup(vars->oldpwd);
	if (!temp)
		return (NULL);
	if (access(temp, F_OK) && chdir(temp) == 0)
		reset_old_pwd(vars, temp);
	return (free(temp), temp = NULL, NULL);
}

char	*go_slash(char **token, int x, t_buildins *vars)
{
	if ((token[x + 1][1] == '/' && token[x + 1][2] == '\0')
		|| (token[x + 1][1] == '\0'
		|| (token[x + 1][1] == '/' && token[x + 1][2] == '/')))
	{
		if (access(token[x + 1], F_OK) && chdir(token[x + 1]) == 0)
			reset_old_pwd(vars, token[x + 1]);
	}
	return (NULL);
}

char	*go_full_path(char **token, int x, t_buildins *vars)
{
	if (access(token[x + 1], F_OK) == 0)
	{
		if (access(token[x + 1], F_OK) && chdir(token[x + 1]) == 0)
			reset_old_pwd(vars, token[x + 1]);
	}
	else
		ft_putendl_fd("No such file or directory", 2);
	return (NULL);
}

char	*fill_path(t_buildins *vars, char **token, int x)
{
	char	*temp;

	temp = NULL;
	if (token[x + 1][0] == '-' && token[x + 1][1] == '\0')
		temp = go_back(vars, temp);
	else if (token[x + 1][0] == '.' && token[x + 1][1] == '.' && token[x + 1][2] == '\0')
		temp = go_up(vars, temp);
	else if (token[x + 1][0] == '.' && token[x + 1][1] == '\0')
		return (NULL);
	else if (token[x + 1][0] == '/' && token[x + 1][1] != '\0'
		&& token[x + 1][1] != '/')
		temp = go_full_path(token, x, vars);
	else if (token[x + 1][0] == '/')
		temp = go_slash(token, x, vars);
	else
		temp = add_to_path(vars, token[x + 1]);
	return (temp);
}

int	cd(t_buildins *vars, char **token)
{
	int		x;
	char	*path;

	x = find_arg(token, "cd");
	path = NULL;
	if (!token || !ft_strcmp(token[x], "cd"))
		return (1);
	else if (token[x + 1] == NULL)
		return (cd_home(vars));
	else if (token[x + 1] != NULL)
	{
		path = fill_path(vars, token, x);
		if (!path)
			return (0);
		return (cd_path(vars, path));
	}
	return (1);
}

void	set_cdpath(t_buildins *vars, char **token)
{
	char	**temp;
	int		x;

	temp = NULL;
	x = find_arg(token, "export");
	if (ft_strcmp(token[x], "export") && ft_strcmp(token[x + 1], "CDPATH")
		&& token[x + 2])
	{
		temp = ft_split(token[x + 2], ':');
		if (!temp)
			err_or("split");
		while (*temp)
		{
			if (access(*temp, F_OK) == -1)
			{
				ft_free_double(temp);
				err_or("access");
			}
			temp++;
		}
		ft_free_double(temp);
		vars->cdpath = ft_strdup(token[x + 2]);
		if (!vars->cdpath)
			err_or("strdup");
	}
}

void	get_cdpath(t_buildins *vars)
{
	if (!vars->cdpath)
		vars->cdpath = ft_strdup("\n");
	else
		err_or("not done yet");
}
