/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buildins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbaumeis <lbaumeis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/27 12:49:02 by lbaumeis          #+#    #+#             */
/*   Updated: 2024/08/06 16:37:22 by lbaumeis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILDINS_H
# define BUILDINS_H

# include <features.h>
# include <signal.h>
# include <sys/signal.h>
# include <term.h>
# include <dirent.h>
# include <sys/ioctl.h>
# include "../../libft/libft.h"
# include <sys/wait.h>
# include <stdlib.h>
# include <stddef.h>
# include <unistd.h>
# include <string.h>
# include <stdio.h>
# include <fcntl.h>
# include <errno.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <complex.h>
# include <stdbool.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <dirent.h>

typedef struct s_buildins
{
	char	**envp;
	char	**menv;
	char	*mpath;
	char	**xport;
	char	*home;
	char	*oldpwd;
	char	*pwd;
}			t_buildins;

/*UTILS*/
int		how_many(char **s, char *o);
bool	is_access(char *dir);
void	err_or(char *s);
int		find_arg(char **s, char *a);
void	buildins_init(t_buildins *vars);

/*UTILS2*/
int		find_str_part(char **str, char *tok);
//char	*strcpy_from(char *v_part);
char	*strcpy_until(char *v_part);
char	**copy_arr_env(t_buildins *vars);
bool	check_quotes(char *token);
bool	valid_env(t_buildins *vars, char *tok);

/*PWD*/
void	reset_old_pwd(t_buildins *vars, char *path);
void	join_oldpwd(t_buildins *vars, char **temp, char *oldpwd);
void	go_up_oldpwd(t_buildins *vars);

/*ENV*/
void	get_pwd(t_buildins *vars);
char	*get_env(t_buildins *vars, char *str);
void	get_menv(t_buildins *vars);

/*CD_FIND_PATH*/
int		add_to_path(t_buildins *vars, char *t);
int		go_back(t_buildins *vars, int print);
char	*check_slash(char *tok, char *temp);
int		go_slash(t_buildins *vars, char **token, int x);
int		go_full_path(t_buildins *vars, char **token, int x);

/*CD*/
int		cd_home(t_buildins *vars);
int		fill_path(t_buildins *vars, char **token, int x);
int		cd(t_buildins *vars, char **token);

/*ECHO*/
void	do_echo(t_buildins *vars, char **token, int x);
bool	check_n(char *token);
void	echo(t_buildins *vars, char **token);

/*EXPAND*/
char	*xpand(t_buildins *vars, char **token, int x);

/*EXPORT*/
bool	sorted(char **arr);
void	swap(char **arr, int x);
char	**sort_arr(t_buildins *vars);
char	*exp_whole(t_buildins *vars, char **arr, int y);
void	combine_export(t_buildins *vars);

/*SET_EXPORT*/
char	*no_quotes(char *token, int x, int y);
char	*has_quotes(char *token, int x, int y);
char	*modify_quotes(char *token);
void	update_export(t_buildins *vars, char *tok, char *token);
void	set_export(t_buildins *vars, char **token);

/*ADD_EXPORT*/
int		ft_strcmp_until(const char *s1, const char *s2);
char	*create_add_export(char *token);
bool	resorted(char **arr);
char	**resort_arr(char **arr);
void	add_to_env(t_buildins *vars, char *add);
void	add_to_export(t_buildins *vars, char *token);

/*UNSET*/
void	update_unset(t_buildins *vars, char *tok);
void	update_unset_exp(t_buildins *vars, char *tok);
void	unset(t_buildins *vars, char **token);

#endif
