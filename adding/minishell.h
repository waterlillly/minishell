/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbaumeis <lbaumeis@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 16:39:43 by lbaumeis          #+#    #+#             */
/*   Updated: 2024/08/14 15:57:04 by lbaumeis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft/libft.h"
# include <unistd.h>
# include <stdbool.h>
# include <stdio.h>
# include <string.h>
# include <stdlib.h>
# include <stddef.h>
# include <errno.h>
# include <complex.h>
# include <fcntl.h>
# include <features.h>
# include <term.h>
# include <dirent.h>
# include <signal.h>
# include <sys/ioctl.h>
# include <sys/wait.h>
# include <sys/signal.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <readline/readline.h>
# include <readline/history.h>

# define BUFF_SIZE 8
# define MAX_FD 1024 + 1
# define RET_VALUE(ret)	ret > 0 ? 1 : ret

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
	int		n_lessalloc;
	int		sum;
}	t_raw_in;

typedef struct s_minishell_l
{
	char					*input;
	char					*str;
	t_token					token;
	struct s_minishell_l	*next;
	struct s_minishell_l	*prev;
}	t_minishell_l;

typedef struct s_minishell_p
{
	char					**str;
	int						str_len;
	char					*infile;
	char					*outfile;
	bool					std_out;
	t_minishell_l			*redirect;
	struct s_minishell_p	*next;
	struct s_minishell_p	*prev;
}	t_minishell_p;

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
	t_minishell_p	*parser;
	
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

void	exit_shell(t_pipex *p, char *str, int exit_code);
int		error(char *str, int code);
bool	is_buildin(char *s);
void	do_this(t_pipex *p);

/*____________________LEXPARSE____________________*/
void	print_parsed(t_minishell_p *in);
void	init_raw(t_raw_in *in);
void	free_raw(t_raw_in *in);
char	*ft_strnstr_q(const char *big, const char *little, size_t len);
int		count_hd(char *str);
int		open_line(char *input);

//int 			error(char *str, int code);
void			remove_dq(char **in, int len);
void			remove_sq(char **in, int len);
int				double_count(char *input);
int				single_count(char *input);
int 			open_quotes(char *input);
int				get_line_cnc(t_raw_in *in);
void			ft_split_shell(t_raw_in *in);
int				is_sep(char *charset, char c);
t_minishell_l	*lexer(t_raw_in *in);
int				check_syntax(char *input);
void			set_first(t_raw_in *in, char *line);
char			*skip_q(char *str);
void			set_op(t_raw_in *in, char *line);
t_minishell_l	*ft_lstlast_lex(t_minishell_l *lst);
void			ft_lstadd_back_lex(t_minishell_l **alst, t_minishell_l *new);
t_minishell_p	*parser(t_minishell_l *in, t_raw_in *raw);
t_minishell_l	*ft_lstfirst_lex(t_minishell_l *lst);

/*____________________PIPEX____________________*/
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
void	init_p(t_pipex *p, t_minishell_p *parser);
void	first_init(t_pipex *p, char **envp);

/*PROCESSES*/
void	first(t_pipex *p, int *c);
void	middle(t_pipex *p, int *c);
void	last(t_pipex *p, int *c);
void	do_child(t_pipex *p, int *c);

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

/*____________________BUILDINS____________________*/
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
char	*add_quotes(char *token);
void	update_export(t_pipex *p, char *tok, char *token);
void	set_export(t_pipex *p, char **token);

/*ADD_EXPORT*/
int		ft_strcmp_until(const char *s1, const char *s2);
char	*create_add_export(char *token);
bool	resorted(char **arr);
char	**resort_arr(char **arr);
void	add_to_env(t_pipex *p, char *add);
void	add_to_export(t_pipex *p, char *token);

/*UNSET*/
void	update_unset(t_pipex *p, char *tok);
void	update_unset_exp(t_pipex *p, char *tok);
void	unset(t_pipex *p, char **token);

#endif
