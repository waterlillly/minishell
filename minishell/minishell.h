/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbaumeis <lbaumeis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 16:25:59 by lbaumeis          #+#    #+#             */
/*   Updated: 2024/08/07 16:15:09 by lbaumeis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libftultra/libftultra.h"
# include <features.h>
# include <signal.h>
# include <sys/signal.h>
# include <term.h>
# include <dirent.h>
# include <sys/ioctl.h>
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

# define BUFF_SIZE 8
# define MAX_FD 1024 + 1
# define RET_VALUE(ret)	ret > 0 ? 1 : ret

typedef struct s_exec t_exec;
typedef enum e_token t_token;
typedef struct s_raw_in t_raw_in;
typedef struct s_mini_l t_mini_l;
typedef struct s_mini_p t_mini_p;

typedef struct s_exec
{
	pid_t	*pid;
	int		**pip;
	char	**av;
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
	char	**menv;
	char	*mpath;
	char	**xport;
	char	*home;
	char	*oldpwd;
	char	*pwd;
	//bool	alot;
}			t_exec;

typedef enum e_token
{
	PIPE = 1,
	BIGGER,
	BIGGERBIGGER,
	SMALLER,
	HEREDOC
}	t_token;

typedef struct s_raw_in
{
	char	*input;
	char	*line;
	char	**del_s;
	char	**del_str;
	char	**out;
	int		n_chd;
	int		n_hd;
	bool	open_pipe;
	int		n_pipe;
	int		n_red;
	int		n_words;
}	t_raw_in;

typedef struct s_mini_l
{
	char			*input;
	char			*str;
	t_token			token;
	t_mini_l		*next;
	t_mini_l		*prev;
}	t_mini_l;

typedef struct s_mini_p
{
	char			**str;
	int				redir;
	char			*infile;
	char			*outfile;
	bool			std_out;
	t_mini_l		*redirect;
	t_mini_p		*next;
	t_mini_p		*prev;
}	t_mini_p;

typedef struct s_ms
{
	t_raw_in	*in;
	t_mini_l	*lex;
	t_mini_p	*parse;
	t_exec		*e;
}	t_ms;

void	init_raw(t_raw_in *in);
//void	init_mini_part2(t_ms *ms);
//void	init_mini_part1(t_ms *ms);
int 	error(t_raw_in *in, char *str, int code);

/*____________________MINISHELL____________________*/

void	remove_q(t_raw_in *in);
int		double_count(char *input);
int		single_count(char *input);
int 	open_quotes(char *input);

/*MINISHELL*/
int		open_line(char *input);
int		is_sep(char *charset, char c);
int		count_hd(char *str);
char	*skip_q(char *str);
char	*ft_strnstr_q(const char *big, const char *little, size_t len);
void	set_hd(t_raw_in *in, char *line);
void	set_op(t_raw_in *in, char *line);
void	set_first(t_raw_in *in, char *line);
int		is_invalid(char c);
int		check_red(char *str);
int		check_spipe(char *str);
int		check_pipe(char *str);
int		check_syntax(char *input);
void	get_hd(t_raw_in *in);
void	get_pipe(t_raw_in *in);
int		get_line_cnc(t_raw_in *in);
void	free_raw(t_raw_in *in);

/*____________________PIPEX____________________*/

/*PIPEX*/
void	find_path(t_ms *ms);
char	*is_exec(t_ms *ms);
void	exec_cmd(t_ms *ms);

/*CLOSE_FREE*/
void	close_pipes(t_ms *ms);
void	close_all(t_ms *ms);
void	free_double(char **str);
void	err_free_two(t_ms *ms);
void	err_free(t_ms *ms);

/*INIT*/
void	check_filein(t_ms *ms);
void	check_fileout(t_ms *ms);
void 	init_pipes(t_ms *ms);
//void	check_in(t_ms *ms);
//void	check_out(t_ms *ms);

/*PROCESSES*/
void	first(t_ms *ms, int *c);
void	middle(t_ms *ms, int *c);
void	last(t_ms *ms, int *c);
void	do_child(t_ms *ms, int *c);

/*HERE_DOC*/
void	get_cur_cwd(t_ms *ms);
void	first_heredoc(t_ms *ms);
void	adjust_struct(t_ms *ms);
void	adjust_struct_here(t_ms *ms);
void	here_or_not(t_ms *ms);

/*EXTRA_CASES*/
void	single_exec(t_ms *ms);
void	no_infile_exec(t_ms *ms, int *c);
//void	read_cwd(t_pipex *p);

/*____________________BUILDINS____________________*/

/*UTILS*/
int		how_many(char **s, char *o);
bool	is_access(char *dir);
int		find_arg(char **s, char *a);
void	err_free_buildins(t_ms *ms);

/*UTILS2*/
int		find_str_part(char **str, char *tok);
char	*strcpy_until(char *v_part);
char	**copy_arr_env(t_ms *ms);
bool	check_quotes(char *token);
bool	valid_env(t_ms *ms, char *tok);

/*PWD*/
void	reset_old_pwd(t_ms *ms, char *path);
void	join_oldpwd(t_ms *ms, char **temp, char *oldpwd);
void	go_up_oldpwd(t_ms *ms);

/*ENV*/
void	get_pwd(t_ms *ms);
char	*get_env(t_ms *ms, char *str);
void	get_menv(t_ms *ms, char **envp);

/*CD_FIND_PATH*/
int		add_to_path(t_ms *ms, char *t);
int		go_back(t_ms *ms, int print);
char	*check_slash(t_ms *ms, char *tok, char *temp);
int		go_slash(t_ms *ms, char **token, int x);
int		go_full_path(t_ms *ms, char **token, int x);

/*CD*/
int		cd_home(t_ms *ms);
int		fill_path(t_ms *ms, char **token, int x);
int		cd(t_ms *ms, char **token);

/*ECHO*/
void	do_echo(t_ms *ms, char **token, int x);
bool	check_n(char *token);
void	echo(t_ms *ms, char **token);

/*EXPAND*/
char	*xpand(t_ms *ms, char **token, int x);

/*EXPORT*/
bool	sorted(char **arr);
void	swap(char **arr, int x);
char	**sort_arr(t_ms *ms);
char	*exp_whole(t_ms *ms, char **arr, int y);
void	combine_export(t_ms *ms);

/*SET_EXPORT*/
char	*no_quotes(char *token, int x, int y);
char	*has_quotes(char *token, int x, int y);
char	*modify_quotes(char *token);
void	update_export(t_ms *ms, char *tok, char *token);
void	set_export(t_ms *ms, char **token);

/*ADD_EXPORT*/
int		ft_strcmp_until(const char *s1, const char *s2);
char	*create_add_export(t_ms *ms, char *token);
bool	resorted(char **arr);
char	**resort_arr(char **arr);
void	add_to_env(t_ms *ms, char *add);
void	add_to_export(t_ms *ms, char *token);

/*UNSET*/
void	update_unset(t_ms *ms, char *tok);
void	update_unset_exp(t_ms *ms, char *tok);
void	unset(t_ms *ms, char **token);

#endif