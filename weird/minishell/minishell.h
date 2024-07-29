/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbaumeis <lbaumeis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 11:17:44 by lbaumeis          #+#    #+#             */
/*   Updated: 2024/07/29 14:20:59 by lbaumeis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../execution/pipex/pipex.h"
# include "../execution/buildins/buildins.h"

typedef struct s_buildins
{
	char	**envp;
	char	*cdpath;
	char	**menv;
	char	*menvp;
	char	**export;
	char	*home;
	char	*oldpwd;
	char	*pwd;
}			t_buildins;

typedef struct s_pipex
{
	pid_t	*pid;
	int		**pip;
	char	**av;
	char	**envp;
	char	*cwd;
	int		ac;
	int		x;//first cmd
	int		copy_stdout;
	int		filein;
	int		fileout;
	bool	in;
	bool	out;
	bool	here;
	int		status;
	int		cmd_count;
	char	*delimiter;
	char	**args;
	char	**paths;
	char	*path;
	char	*executable;
	char	*part;
	char	*cmd;
	t_buildins	*vars;
}			t_pipex;


void		check_args(t_pipex *p, int ac, char **av, t_buildins *vars);
int			check_buildins(t_pipex *p);

#endif
