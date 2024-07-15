#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

typedef struct s_minishell_l
{
	char	**input;
	int		*markers:
}	t_minishell_l;

typedef struct s_minishell_p
{
	t_minishell_l	*lexed;
	t_cmd			*table;
}	t_minishell_p;

typedef struct s_redirect
{
	int		type;
	char	*filename;
}	t_redirect;

typedef struct s_pipecmd
{
	char				*cmd;
	char				*arg;
	char				*option;
	struct	s_pipecmp	*next;
}	t_pipecmd;

typedef struct s_cmd
{
	t_pipecmd	*pipecmd;
	t_redirect	*redirect;
}	t_cmd;

#endif