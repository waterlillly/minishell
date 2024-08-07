/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbaumeis <lbaumeis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/28 11:38:34 by lbaumeis          #+#    #+#             */
/*   Updated: 2024/08/07 11:32:21 by lbaumeis         ###   ########.fr       */
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
		get_env(vars, "HOME");
	if (is_access(vars->home))
	{
		reset_old_pwd(vars, vars->home);
		return (chdir(vars->home));
	}
	return (error(vars->home), 1);
}

int	fill_path(t_buildins *vars, char **token, int x)
{
	if (token[x + 1][0] == '-' && token[x + 1][1] == '\0')
	{
		if (ft_strcmp(vars->pwd, vars->oldpwd))
			go_up_oldpwd(vars);
		return (go_back(vars, 1));
	}
	else if (token[x + 1][0] == '.' && token[x + 1][1] == '.'
		&& token[x + 1][2] == '\0')
	{
		go_up_oldpwd(vars);
		return (go_back(vars, 0));
	}
	else if (token[x + 1][0] == '.' && token[x + 1][1] == '\0')
		return (0);
	else if (token[x + 1][0] == '/' && token[x + 1][1] != '\0'
		&& token[x + 1][1] != '/')
		return (go_full_path(vars, token, x));
	else if (token[x + 1][0] == '/')
		return (go_slash(vars, token, x));
	else
		return (add_to_path(vars, token[x + 1]));
	return (error(token[x + 1]), 1);
}

int	cd(t_buildins *vars, char **token)
{
	int		x;

	x = find_arg(token, "cd");
	if (!token || !ft_strcmp(token[x], "cd"))
		return (error("command not found"), 1);
	else if (token[x + 1] == NULL || ft_strcmp(token[x + 1], "#")
		|| (token[x + 1][0] == '-' && token[x + 1][1] == '-'
		&& token[x + 1][2] == '\0'))
		return (cd_home(vars));
	else if (token[x + 1] != NULL)
		return (fill_path(vars, token, x));
	return (error(token[x + 1]), 1);
}
