/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbaumeis <lbaumeis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 16:39:43 by lbaumeis          #+#    #+#             */
/*   Updated: 2024/09/23 22:06:46 by lbaumeis         ###   ########.fr       */
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
	PIPE = 1,//
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
	int						str_len;//
	char					*infile;//
	char					*outfile;//
	bool					std_out;//
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
	long	status;
	int		copy_stdin;
	int		copy_stdout;
	int		filein;
	int		fileout;
	char	*here;
	int		cmd_count;
	char	**paths;
	char	*path;
	char	*executable;
	char	*part;
	char	*cmd;
}			t_pipex;

/*MAIN*/
void 	free_parse(t_minishell_p *in);
void	refresh_init(t_pipex *p, t_raw_in *input, t_minishell_p **pars);
int		do_stuff(t_pipex *p, int c, t_minishell_p *pars);
bool	run(t_pipex *p, t_raw_in *input, t_minishell_p **pars);

/*EXIT*/
void	exit_shell(t_pipex *p, t_minishell_p *pars, t_raw_in *input, char *str);
int		error(char *str, int code);
void	free_p_rest(t_pipex *p);
void	free_everything(t_pipex *p, t_minishell_p *pars, t_raw_in *input);
bool	check_exit(t_pipex *p, int *c, t_minishell_p **pars);

/*MORE_CMDS*/
bool	is_buildin(char *s);
int		do_this(t_pipex *p, t_minishell_p *pars);

/*PRE_EXEC*/
int		check_access(t_pipex *p, char **cmd, t_minishell_p *pars);
int		check(t_pipex *p, t_minishell_p *pars);
bool	valid_cmd(char **str, t_pipex *p);
char	*loop_cmd_check(t_pipex *p, t_minishell_p *pars, int x);
char	**check_cmd(t_pipex *p, t_minishell_p *pars);

/*EXECUTE*/
int		redirect(t_pipex *p, int c, t_minishell_p *pars);
int		execute(t_pipex *p, int c, t_minishell_p *pars);

/*START*/
void	sig_int(int	num);
void	sig_quit(int num);
void	get_input(t_pipex *p, t_minishell_l **lex, t_minishell_p **pars, t_raw_in *input);

/*REDIR*/
void	check_filein(t_pipex *p, t_minishell_p *pars);
void	check_fileout(t_pipex *p, t_minishell_p *pars);

/*____________________LEXPARSE____________________*/
void	print_parsed(t_minishell_p *in);
void	init_raw(t_raw_in *in);
void	free_raw(t_raw_in *in);
char	*ft_strnstr_q(const char *big, const char *little, size_t len);
int		count_hd(char *str);
int		open_line(char *input);

void			remove_q(char **in, int len);
void			remove_sq(char **in, int len);
int				double_count(char *input);
int				single_count(char *input);
int 			open_quotes(char *input);
int				get_line_cnc(t_raw_in *in, t_pipex *p);
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
int				is_oq(char	c, int *dq, int *sq);
t_minishell_p	*ft_lstfirst_parse(t_minishell_p *lst);
void			free_lex(t_minishell_l *in);

/*____________________PIPEX____________________*/
/*PIPEX*/
char	*is_exec(t_pipex *p);
int		do_heredoc(t_pipex *p, t_minishell_p *pars);
int		exec_cmd(t_pipex *p, t_minishell_p *pars);

/*ERROR*/
void	closing(t_pipex *p);
void	close_pipes(t_pipex *p);
void	close_all(t_pipex *p);
void	err_free(t_pipex *p);

/*INIT*/
void 	init_pipes(t_pipex *p);
void	init_p(t_pipex *p, t_minishell_p *pars);
int		first_init(t_pipex *p, char **envp);

/*____________________BUILDINS____________________*/
/*UTILS*/
bool	is_access(char *dir);
int		find_arg(char **s, char *a);
int		find_str_part(char **str, char *tok);
char	*strcpy_until(char *v_part);
int		ft_strcmp_until(const char *s1, const char *s2);
char	**update_free_arr(char **old, char **new);

/*QUOTES*/
char	*add_quotes(char *token);
char	*remove_quotes(char *s);
int		check_d_q(char *token);
bool	check_s_q(char *token);
bool	s_out_q(char *tok);
bool	d_out_q(char *tok);

/*PWD*/
void	reset_old_pwd(t_pipex *p, char *path);
int		get_int(char **temp);
int		join_oldpwd(t_pipex *p, char **temp, char *oldpwd);
int		go_up_oldpwd(t_pipex *p);

/*ENV*/
void	copy_arr_env(t_pipex *p, char **arr);
bool	valid_env(t_pipex *p, char *tok);
char	*get_env(t_pipex *p, char *str);
int		get_menv(t_pipex *p, char **envp);
int		buildins_init(t_pipex *p, char **envp);

/*BACKUP*/
//int		backup_env(t_pipex *p, char *temp);
//int		backup_xport(t_pipex *p, char *temp);
//int		backup(t_pipex *p);

/*CD_FIND_PATH*/
int		add_to_path(t_pipex *p, char *t);
int		go_back(t_pipex *p, int print);
void	check_print(char *s);
int		go_slash(t_pipex *p, char **token);
int		go_full_path(t_pipex *p, char **token);

/*CD*/
int		cd_home(t_pipex *p);
int		go_back_minus(t_pipex *p, int print);
int		fill_path(t_pipex *p, char **token);
int		cd(t_pipex *p, char **token);

/*ECHO*/
char	*split_and_xpand(t_pipex *p, char **s);
int		dollar_count(char *s);
bool	even_q(char *s);
int		do_echo(t_pipex *p, char **token, int x);
bool	check_n(char *token);
int		echo(t_pipex *p, char **token);

/*ECHO_SPLIT*/
int		countstrs(char *s, char c);
int		do_split(char *s, char c, int pos_a);
char	**echo_split(char *s, int c);

/*EXPAND*/
bool	only_dollars(char *tok);
char	*rm_out_q(char *tok);
int		multi_q(char *token);
char	*rm_q(char *token);
char	*xpand(t_pipex *p, char **token, int x);

/*XPORT*/
char	*exp_whole(t_pipex *p, char **arr, int y);
int		combine_export(t_pipex *p);
char	*create_add_export(char *token);
int		add_to_env(t_pipex *p, char *add);
int		add_to_export(t_pipex *p, char *token);

/*SET_EXPORT*/
int		update_export(t_pipex *p, char *tok, char *token);
int		set_export(t_pipex *p, char **token);
int		update(t_pipex *p, char *set, char *tok);
int		update_both(t_pipex *p);

/*SORTING*/
bool	sorted(char **arr);
void	swap(char **arr, int x);
void	sort_arr(t_pipex *p, char **arr);
bool	resorted(char **arr);
void	resort_arr(char **arr);

/*UNSET*/
int		update_unset(t_pipex *p, char *tok);
int		update_unset_exp(t_pipex *p, char *tok);
int		unset(t_pipex *p, char **token);

#endif
