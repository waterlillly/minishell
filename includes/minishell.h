#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdbool.h>
# include <stddef.h>
# include "../srcs/libft/libft.h"
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
	int		n_ds;
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
	int						redir;
	char					*infile;
	char					*outfile;
	bool					std_out;
	t_minishell_l			*redirect;
	struct s_minishell_p	*next;
	struct s_minishell_p	*prev;
}	t_minishell_p;

int 			error(char *str, int code);
void			remove_q(t_raw_in *in);
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






#endif