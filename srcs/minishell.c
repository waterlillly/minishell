#include <stdio.h>
#include "get_next_line.h"
#include "./libft/libft.h"
#include "minishell.h"

int	word(char *input)
{
	
}

size_t	count_lex(char *str)
{
	size_t	i;

	i = 0;
	while (*str)
	{
		while (*str == ' ' || *str = 9)
			str++;
		if (word(str) && ++i)
			str = eow(str);
	}
	return (i);
}

t_minishell_l	*ft_lstnew_lex(char *content, int type)
{
	t_minishell_l	*out;

	out = (t_list *)malloc(sizeof(*out));
	if (!out)
		return (out);
	if (!type)
		out->input = content;
	else
		out->input = NULL;
	out->token = type;
	out->next = NULL;
	out->prev = NULL;
	return (out);
}

t_minishell_l	*create_nodes_lex(char **input, size_t len)
{
	t_minishell_l	*out;
	t_minishell_l	*tmp;
	int	i;

	
}

void	lexer(t_minishell_l	*lex, char *input)
{
	size_t	n_nodes;

	n = count_lex(input);
	lex = create_nodes_lex(input, n);
}

int	main(void)
{
	static char		*line[2];
	while (1)
	{
		ft_putstr_fd("this is a legit minishell $>", 1);
		get_next_line(0, line);
		
		if (!ft_strncmp("done", line[0], 4))
			return (free(line[0]), 0);
		ft_putendl_fd(line[0], 1);
	}
}