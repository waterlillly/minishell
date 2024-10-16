/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbaumeis <lbaumeis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 16:39:43 by lbaumeis          #+#    #+#             */
/*   Updated: 2024/10/16 16:56:52 by lbaumeis         ###   ########.fr       */
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
# include <sys/ioctl.h>

# define BUFF_SIZE 8
# define MAX_FD 1024 + 1
# define RET_VALUE(ret)	ret > 0 ? 1 : ret

extern volatile sig_atomic_t g_signal;

typedef enum e_token
{
	PIPE = 1,
	BIGGER,
	BIGGERBIGGER,
	SMALLER,
	HEREDOC
}	t_token;

typedef enum e_mode
{
	INTER = 1,
	CHILD,
	HD,
	LEVEL
}	t_mode;

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
	int		exit;
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
	char					**ps;
	int						str_len;
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
	char	**xport;
	char	*home;
	char	*oldpwd;
	char	*pwd;
	pid_t	*pid;
	int		**pip;
	int		status;
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
	bool	exit;
	int		exit_count;
	t_mode	mode;
}			t_pipex;

/*MAIN*/
void	refresh_init(t_pipex *p, t_raw_in *input, t_minishell_p **pars);
int		do_stuff(t_pipex *p, int c, t_minishell_p *pars);
bool	run(t_pipex *p, t_raw_in *input, t_minishell_p **pars);

/*FREE*/
void	free_p_rest(t_pipex *p);
void	free_everything(t_pipex *p, t_minishell_p *pars, t_raw_in *input);
void 	free_parse(t_minishell_p *in);
void	err_free(t_pipex *p);

/*EXIT*/
void	exit_shell(t_pipex *p, t_minishell_p *pars, t_raw_in *input, char *str);
int		error(char *str, int code);
char	*check_exit(t_pipex *p, t_minishell_p *pars);

/*SIGNALS*/
void	sig_int(int	num);
void	sig_int_hd(int num);
void	sig_int_child(int num);
void	sig_quit_child(int num);
void	sig_quit(int num);
void	sig_init(t_pipex *p, int hd);
void	set_mode_s(t_pipex *p, int c);

/*START*/
void	get_input(t_pipex *p, t_minishell_l **lex, t_minishell_p **pars, t_raw_in *input);

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

/*____________________EXEC____________________*/
/*PIPEX*/
char	*is_exec(t_pipex *p);
int		do_heredoc(t_pipex *p, t_minishell_p *pars);
int		exec_cmd(t_pipex *p, t_minishell_p *pars);

/*CLOSE_PIPES*/
void	closing(t_pipex *p);
void	close_pipes(t_pipex *p);
void	close_all(t_pipex *p);

/*INIT*/
void 	init_pipes(t_pipex *p);
void	init_p(t_pipex *p, t_minishell_p *pars);
int		first_init(t_pipex *p, char **envp);

/*REDIR*/
bool	check_filein(t_pipex *p, t_minishell_p *pars);
bool	check_fileout(t_pipex *p, t_minishell_p *pars);

/*MORE_CMDS*/
bool	is_buildin(char *s);
int		do_this(t_pipex *p, t_minishell_p *pars);

/*PRE_EXEC*/
int		check_access(t_pipex *p, t_minishell_p *pars);
int		check(t_pipex *p, t_minishell_p *pars);
bool	valid_cmd(char **str, t_pipex *p);
char	**check_cmd(t_minishell_p *pars);

/*EXECUTE*/
int		redirect(t_pipex *p, int c, t_minishell_p *pars);
int		execute(t_pipex *p, int c, t_minishell_p *pars);

/*UTILS*/
bool	is_access(char *dir);
int		find_arg(char **s, char *a);
int		find_str_part(char **str, char *tok);
char	*strcpy_until(char *v_part);
int		ft_strcmp_until(const char *s1, const char *s2);
char	**update_free_arr(char **old, char **new);
int		ft_strsrc(char *s, int c);

/*QUOTES*/
char	*add_quotes(char *token);
char	*remove_quotes(char *s);
int		check_d_q(char *token);
bool	check_s_q(char *token);
bool	s_out_q(char *tok);
bool	d_out_q(char *tok);
bool	only_quotes(char *s);
int		only_q(char *s, int q);
int		count_q(char *s, int q);

/*ENV*/
void	copy_arr_env(t_pipex *p, char **arr);
bool	valid_env(t_pipex *p, char *tok);
char	*get_env(t_pipex *p, char *str);
int		get_menv(t_pipex *p, char **envp);
int		buildins_init(t_pipex *p, char **envp);

/*CD*/
int		cd(t_pipex *p, char **token);

/*ECHO*/
char	*split_and_xpand(t_pipex *p, char **s);
int		dollar_count(char *s);
bool	even_q(char *s);
int		do_echo(char **token, int x, int start);
bool	check_n(char *token);
int		echo(char **token);

/*ECHO_SPLIT*/
char	**rewrite(char **s, int c);
char	**reformat(char **s);
bool	is_quote(int q);
int		xpd_count(char *s);
char	**xpd_split(char *s);
void	xpd(t_pipex *p, t_minishell_p *pars);

/*XPD SPACE*/
int		count_space_strs(char *str, int q);
int		space_split(char *s, int d, int pa);
char	**xpd_3_split(char *str, int q);
char	**d_q_space(char **s);

/*XPD DOLLAR*/
int		count_dlr_strs(char *s, char c);
int		dlr_split(char *s, int d, int pa);
char	**xpd_2_split(char *str, int q);

/*XPD QUOTES*/
int		count_q_strs(char *str, int q);
int		q_split(char *s, int q, int pa);
char	**xpd_1_split(char *str, int q);

/*XPD SLASH*/
int		count_slash_strs(char *str, int q);
int		slash_split(char *s, int q, int pa);
char	**xpd_slash_split(char *str, int q);

/*XPD*/
char	**xpd_dollar(char **s);
char	**xpd_space(char **s);
char	**xpd_single(char **s);
char	**xpd_double(char **s);
char	**xpd_slash(char **s);
char	**xpd_start(t_minishell_p *pars, int i);

/*XPD_UTILS*/
char	**arrjoin(char **old, char **new);
char	**ft_arrdup(char **s);

/*EXPAND*/
bool	only_dollars(char *tok);
char	*rm_out_q(char *tok);
int		multi_q(char *token);
char	*rm_q(char *token);
char	*xpand(t_pipex *p, char **token, int x, int lead);

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
void	check_unset(t_pipex *p);

#endif
