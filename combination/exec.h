/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbaumeis <lbaumeis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 16:39:43 by lbaumeis          #+#    #+#             */
/*   Updated: 2024/08/12 02:29:49 by lbaumeis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

# include <features.h>
# include <signal.h>
# include <sys/signal.h>
# include <term.h>
# include <dirent.h>
# include <sys/ioctl.h>
# include "libft/libft.h"
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
/*
typedef struct s_args
{
	char	*arg;
	t_args	*next;
	t_args	*prev;
	bool	pipe;
	bool	in;
	bool	out;
	bool	hd;
	bool	appd;
	bool	cmd;//execve or buildin
}	t_args;
*/
typedef struct s_pipex
{
	char	**menv;
	char	*mpath;
	char	**xport;
	char	*home;
	char	*oldpwd;
	char	*pwd;
	
	pid_t	*pid;
	int		**pip;
	int		status;
	int		copy_stdout;
	
	//not needed:
	char	**av;
	int		ac;
	char	*cwd;
	int		x;//first cmd
	int		filein;
	int		fileout;
	bool	in;
	bool	out;
	bool	appd;
	bool	here;
	char	*delimiter;
	int		cmd_count;
	
	//rewrite:
	char	**args;
	char	**paths;
	char	*path;
	char	*executable;
	char	*part;
	char	*cmd;
	//bool	alot;
}			t_pipex;

void	error(t_pipex *p, char *str, int exit_code);
bool	is_buildin(char *s);
void	do_this(t_pipex *p);

/*PIPEX*/
void	find_path(t_pipex *p);
char	*is_exec(t_pipex *p);
int		exec_cmd(t_pipex *p);

/*ERROR*/
void	close_pipes(t_pipex *p);
void	close_all(t_pipex *p);
void	free_double(char **str);
void	err_free_two(t_pipex *p);
void	err_free(t_pipex *p);

/*INIT*/
void	check_filein(t_pipex *p);
void	check_fileout(t_pipex *p);
void 	init_pipes(t_pipex *p);
void	init_p(t_pipex *p);
void	first_init(t_pipex *p, char **envp);

/*PROCESSES*/
void	first(t_pipex *p, int *c);
void	middle(t_pipex *p, int *c);
void	last(t_pipex *p, int *c);
void	do_child(t_pipex *p, int *c);

/*CHECK*/
//int		check_empty(char **av);
//void	check_args(t_pipex *p, int ac, char **av);

/*HERE_DOC*/
void	get_cur_cwd(t_pipex *p);
void	first_heredoc(t_pipex *p);
void	adjust_struct(t_pipex *p);
void	adjust_struct_here(t_pipex *p);
void	here_or_not(t_pipex *p);

/*EXTRA_CASES*/
void	single_exec(t_pipex *p);
void	no_infile_exec(t_pipex *p, int *c);
//void	read_cwd(t_pipex *p);

/*UTILS*/
int		how_many(char **s, char *o);
bool	is_access(char *dir);
int		find_arg(char **s, char *a);
void	buildins_init(t_pipex *p, char **envp);
char	*remove_quotes(char *s);

/*UTILS2*/
int		find_str_part(char **str, char *tok);
char	*strcpy_until(char *v_part);
char	**copy_arr_env(t_pipex *p);
bool	check_quotes(char *token);
bool	valid_env(t_pipex *p, char *tok);

/*PWD*/
void	reset_old_pwd(t_pipex *p, char *path);
void	join_oldpwd(t_pipex *p, char **temp, char *oldpwd);
void	go_up_oldpwd(t_pipex *p);

/*ENV*/
void	get_pwd(t_pipex *p);
char	*get_env(t_pipex *p, char *str);
void	get_menv(t_pipex *p, char **envp);

/*CD_FIND_PATH*/
int		add_to_path(t_pipex *p, char *t);
int		go_back(t_pipex *p, int print);
char	*check_slash(char *tok, char *temp);//t_pipex *p, 
int		go_slash(t_pipex *p, char **token, int x);
int		go_full_path(t_pipex *p, char **token, int x);

/*CD*/
int		cd_home(t_pipex *p);
int		fill_path(t_pipex *p, char **token, int x);
int		cd(t_pipex *p, char **token);

/*ECHO*/
int		do_echo(t_pipex *p, char **token, int x);
bool	check_n(char *token);
void	echo(t_pipex *p, char **token);

/*EXPAND*/
char	*xpand(t_pipex *p, char **token, int x);

/*EXPORT*/
bool	sorted(char **arr);
void	swap(char **arr, int x);
char	**sort_arr(t_pipex *p);
char	*exp_whole(t_pipex *p, char **arr, int y);
void	combine_export(t_pipex *p);

/*SET_EXPORT*/
char	*no_quotes(char *token, int x, int y);
char	*has_quotes(char *token, int x, int y);
char	*modify_quotes(char *token);
void	update_export(t_pipex *p, char *tok, char *token);
void	set_export(t_pipex *p, char **token);

/*ADD_EXPORT*/
int		ft_strcmp_until(const char *s1, const char *s2);
char	*create_add_export(char *token);//t_pipex *p, 
bool	resorted(char **arr);
char	**resort_arr(char **arr);
void	add_to_env(t_pipex *p, char *add);
void	add_to_export(t_pipex *p, char *token);

/*UNSET*/
void	update_unset(t_pipex *p, char *tok);
void	update_unset_exp(t_pipex *p, char *tok);
void	unset(t_pipex *p, char **token);

#endif
