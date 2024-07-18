#include <stdio.h>
#include "get_next_line.h"
#include "./libft/libft.h"
#include "minishell.h"

// int	word(char *input)
// {
// 	return(1);
// }

// size_t	count_lex(char *str)
// {
// 	size_t	i;

// 	i = 0;
// 	while (*str)
// 	{
// 		while (*str == ' ' || *str == 9)
// 			str++;
// 		if (word(str) && ++i)
// 			str = eow(str);
// 	}
// 	return (i);
// }

// t_minishell_l	*ft_lstnew_lex(char *content, int type)
// {
// 	t_minishell_l	*out;

// 	out = (t_list *)malloc(sizeof(*out));
// 	if (!out)
// 		return (out);
// 	if (!type)
// 		out->input = content;
// 	else
// 		out->input = NULL;
// 	out->token = type;
// 	out->next = NULL;
// 	out->prev = NULL;
// 	return (out);
// }

// t_minishell_l	*create_nodes_lex(char **input, size_t len)
// {
// 	t_minishell_l	*out;
// 	t_minishell_l	*tmp;
// 	int	i;

	
// }

// void	lexer(t_minishell_l	*lex, char *input)
// {
// 	size_t	n_nodes;

// 	n = count_lex(input);
// 	lex = create_nodes_lex(input, n);
// }

int	is_heredoc(char *input)
{
	while (*input)	
	{
		if (*input == '<' && *(input + 1) == '<')
			return (1);
		input++;
	}
	return (0);
}

int	double_count(char *input)
{
	int	i;
	int	single_q;

	i = 0;
	single_q = 0;
	while (*input)
	{
		if (*input == '\'')
			single_q++;
		if (*input == '\"' && single_q % 2 == 0)
			i++;
		input++;
	}
	return (i);
}

int	single_count(char *input)
{
	int	i;
	int	double_q;

	i = 0;
	double_q = 0;
	while (*input)
	{
		if (*input == '\"')
			double_q++;
		if (*input == '\'' && double_q % 2 == 0)
			i++;
		input++;
	}
	return (i);
}

int open_quotes(char *input)
{
	char	*tmp;
	int	single_q;
	int	double_q;

	single_q = single_count(input);
	double_q = double_count(input);
	if (single_q % 2)
		return (-1);
	if (double_q % 2)
		return (1);
	return (0);
}

int	open_line(char *input)
{
	static int i = 0;
	if (!input || !*input)
		return (1);
	if (is_heredoc(input))
		return (1);
	if (open_quotes(input))
		return (1);
	// if (only_redir(input))
	// 	return (1);
	return (0);
}

char	*ft_strcat(char *dst, char *src)
{
	int	len_a;
	int	len_b;
	char	*tmp;

	if (!dst)
		len_a = 0;
	else
		len_a = ft_strlen(dst);
	len_b = ft_strlen(src);
	tmp = dst;
	dst = ft_calloc(len_a + len_b + 1, 1);
	if (tmp)
		ft_strlcat(dst, tmp, len_a + 1);
	ft_strlcat(dst, src, len_b + len_a + 1);
	free(tmp);
	return (dst);
}

int	is_sep(char *charset, char c)
{
	while (*charset)
	{
		if (*charset == c)
			return (1);
		charset++;
	}
	return (0);
}

int	count(char *str, char *charset)
{
	int		len_sub;
	int		len_sep;
	int		i;
	int		double_q;
	int		single_q;

	len_sub = 0;
	len_sep = 0;
	single_q = 0;
	double_q = 0;
	i = 0;
	while (str[len_sub + len_sep])
	{
		while (is_sep(charset, str[len_sub + len_sep]) 
			&& str[len_sub + len_sep])
			len_sep++;
		if (!is_sep(charset, str[len_sub + len_sep]) 
			&& str[len_sub + len_sep])
			i++;
		while ((!is_sep(charset, str[len_sub + len_sep]) 
			&& str[len_sub + len_sep]) || (single_q % 2 == 1 || double_q % 2 == 1))
		{
			if (str[len_sub + len_sep] == '\"' && single_q % 2 == 0)
			double_q++;
			if (str[len_sub + len_sep] == '\'' && double_q % 2 == 0)
			single_q++;
			len_sub++;
		}
	}
	return (i);
}

char	*skip(char *str, char *charset, int *len)
{
	int		i;
	int		double_q;
	int		single_q;

	i = 0;
	*len = 0;
	single_q = 0;
	double_q = 0;
	while (is_sep(charset, *str) && *str)
		str++;
	while ((!is_sep(charset, str[i]) && str[i]) || (single_q % 2 == 1 || double_q % 2 == 1))
	{
		if (str[i] == '\"' && single_q % 2 == 0)
			double_q++;
		if (str[i] == '\'' && double_q % 2 == 0)
			single_q++;
		*len = *len + 1;
		i++;
	}
	return (str);
}

char	*ft_strncpy(char *dest, char *src, int n)
{
	int	i;

	i = 0;
	while (src[i] != '\0' && i < n)
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

char	**ft_split_shell(char *str, char *charset)
{
	int		len;
	char	**out;
	int		i;
	char	*str_temp;

	str_temp = str;
	len = 0;
	i = 0;
	if (str == NULL)
	{
		out = (char **)malloc(1 * sizeof(char *));
		out[0] = NULL;
		return (out);
	}
	out = (char **)malloc((count(str_temp, charset) + 1) * sizeof(char *));
	while (i < count(str_temp, charset))
	{
		str = skip(&str[len], charset, &len);
		out[i] = (char *)malloc((len + 1) * sizeof(char));
		ft_strncpy(out[i], str, len);
		i++;
	}
	out[i] = NULL;
	return (out);
}



t_minishell_l	*lex(char *input)
{
	t_minishell_l	*out;
	char			**tmp;

	tmp = ft_split_shell(input, " \t");
	while (*tmp)
	{
		ft_putendl_fd(*tmp, 1);
		tmp++;
	}
}

int	main(void)
{
	t_minishell_l	*lexed;
	static char		*line[2];
	char			*input;
	input = NULL;
	while (1)
	{
		ft_putstr_fd("this is a legit minishell $>", 1);
		get_next_line(0, line);
		input = ft_strcat(input, line[0]);
		free(line[0]);
		// if (open_line(input))
		// 	return (0);
		lexed = lex(input);
		if (!ft_strncmp(input, "done", 4))
			return (0);
		ft_putendl_fd(input, 1);
		free(input);
		input = NULL;
	}
}