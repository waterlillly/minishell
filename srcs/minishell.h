#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdbool.h>
# include <stddef.h>

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
	char	*line[2];
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

typedef struct s_minishell_l
{
	char					*input;
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

#endif