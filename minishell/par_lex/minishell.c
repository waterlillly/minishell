#include "../minishell.h"

/*
int	word(char *input)
{
	return(1);
}

size_t	count_lex(char *str)
{
	size_t	i;

	i = 0;
	while (*str)
	{
		while (*str == ' ' || *str == 9)
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
}*/





/*int	is_heredoc(char *input)
{
	int	h;
	int	d;

	h = 0;
	d = 0;
	while (*input)	
	{
		if (*input == '<' && *(input + 1) == '<')
		{
			input = input + 2;
			while ()
		}
		input++;
	}

	return (0);
} */

int	open_line(char *input)
{
	if (!input || !*input)
		return (1);
	if (open_quotes(input))
		return (1);
	return (0);
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
/*
///////////////////////////////////////////////////////////////////////////////////////////////////
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
	if (is_sep("><|", *str))
		return (red_ig(str, len));
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

char	**ft_split_shell(t_raw_in *in)
{
	int	i;
	int	sum;
	int	j;

	i = -1;
	in->n_words = count(in->input, " \t<>|");
	sum = in->n_words + in->n_hd + in->n_pipe + in->n_red;
	in->out = (char **)ft_calloc(sum + 1, sizeof(char *));
	if (!out)
		return(NULL);
	while (++i < sum)
	{

	}
}
*/
// rewrite this whole split this wont work
/*
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
} */

int	count_hd(char *str)
{
	int	i;

	i = 0;
	while(ft_strnstr(str, "<<", ft_strlen(str)))
	{
		i++;
		str = ft_strnstr(str, "<<", ft_strlen(str)) + 2;
	}
	return (i);
}

char	*skip_q(char *str)
{
	if (*str == '\"')
	{
		str++;
		while (*str != '\"')
			str++;
	}
	else if (*str == '\'')
	{
		str++;
		while (*str != '\'')
			str++;
	}
	return (str);
}
/*
void	count_words(t_raw_in *in, char	*line)
{

}
*/

char	*ft_strnstr_q(const char *big, const char *little, size_t len)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	if ((!big && len == 0) || (len < ft_strlen(little) && !ft_strlen(big)))
		return (NULL);
	if (!*little && big)
		return ((char *)big);
	while (big[i] && i < len)
	{
		while (big[i + j] && big[i + j] == little[j] && i + j < len)
			j++;
		if (!little[j])
			return ((char *)(big + i));
		j = 0;
		i++;
	}
	return (NULL);
}

void	set_hd(t_raw_in *in, char *line)
{
	int	i;
	int j;
	int	k;

	i = in->n_chd - 1;
	in->del_s = ft_realloc_2d(in->del_s, in->n_hd - in->n_chd);
	while (i < in->n_hd - 1 && *line && *(line + 1))
	{
		k = 2;
		j = 0;
		line = skip_q(line);
		if (*line == '<' && *(line + 1) == '<')
		{
			while (is_sep(" \t", *(line + k)))
				k++;
			if (*(line + j + k) == '\"')
			{
				j++;
				while (*(line + j + k) != '\"')
					j++;
				j++;
			}
			else if (*(line + j + k) == '\'')
			{
				j++;
				while (*(line + j + k) != '\'')
					j++;
				j++;
			}
			else
			{
				while (*(line + j + k) && !is_sep(" \t\n\0", *(line + j + k)))
					j++;
			}
			in->del_s[++i] = ft_substr(line, k, j);
			line = line + k + j - 1;
		}
		line++;
	}
	remove_q(in);
}

void	set_op(t_raw_in *in, char *line)
{
	int	len;

	len = ft_strlen(line) - 1;
	while (is_sep(" \t", line[len]))
		len--;
	if (line[len] == '|')
		in->open_pipe = true;
	else
		in->open_pipe = false;
}

void	set_first(t_raw_in *in, char *line)
{
	char *tmp;

	tmp = line;
	while (*line)
	{
		line = skip_q(line);
		if (*line == '>')
		{
			in->n_red++;
			if (*(line + 1) == '>')
				line++;
		}
		if (*line == '<')
		{
			if (*(line + 1) == '<')
			{
				in->n_hd++;
				line++;
			}
			else
				in->n_red++;
		}
		if (*line == '|')
			in->n_pipe++;
		line++;
	}
	set_hd(in, tmp);
	set_op(in, tmp);
}

int	is_invalid(char c)
{
	if (c == '>' || c == '<' || c == '|' || c == '\n' || c == 0)
		return (1);
	return (0);
}

int	check_red(char *str)
{
	int	i;

	while (*str)
	{
		i = 1;
		str = skip_q(str);
		if (*str == '<')
		{
			if (*(str + i) == '<')
				i++;
			while (is_sep(" \t", *(str + i)))
				i++;
			if (is_invalid(*(str + i)))
				return (0);
			str = str + i - 1;
		}
		if (*str == '>')
		{
			if (*(str + i) == '>')
				i++;
			while (is_sep(" \t", *(str + i)))
				i++;
			if (is_invalid(*(str + i)))
				return (0);
			str = str + i - 1;
		}
		str++;
	}
	return (1);
}

int	check_spipe(char *str)
{
	while (is_sep(" \t", *str))
		str++;
	if (*str == '|')
		return (1);
	return (0);
}

int	check_pipe(char *str)
{
	int 	i;

	if (check_spipe(str))
		return (0);
	while (*str)
	{
		i = 1;
		str = skip_q(str);
		if (*str == ';')
			return (0);
		if (*str == '|')
		{
			while (is_sep(" \t", *(str + i)))
				i++;
			if (*(str + i) == '|')
				return (0);
			str = str + i - 1;
		}
		str++;
	}
	return (1);
}

int	check_syntax(char *input)
{
	if (!open_quotes(input) || !check_red(input) || !check_pipe(input))
		return (0);
	return (1);
}

void	get_hd(t_raw_in *in)
{
	in->del_str = ft_realloc_2d(in->del_str, in->n_hd - in->n_chd);
	if (in->n_hd)
	{
		while (in->n_chd < in->n_hd)
		{
			in->line = readline("heredoc> ");
			if (!ft_strcmp_org(in->del_s[in->n_chd], in->line))
			{
				in->n_chd++;
				continue;
			}
			in->del_str[in->n_chd] = ft_strcat(in->del_str[in->n_chd], in->line);
			in->del_str[in->n_chd] = ft_strcat(in->del_str[in->n_chd], "\n");
			free(in->line);
		}
	}
}

void	get_pipe(t_raw_in *in)
{
	if (in->open_pipe)
	{
		in->line = readline("command> ");
		if (!check_syntax(in->line))
			return ((void)error(in, "idk", 1));
		in->input = ft_strcat(in->input, in->line);
		set_first(in, in->line);
	}
}

int	get_line_cnc(t_raw_in *in)
{
	in->line = readline("this is a legit minishell> ");
	if (!check_syntax(in->line))
		return (0);
	in->input = ft_strcat(in->input, in->line);
	set_first(in, in->line);
	free(in->line);
	while (in->open_pipe || in->n_chd < in->n_hd)
	{
		get_hd(in);
		get_pipe(in);
	}
	return (1);
}

void	free_raw(t_raw_in *in)
{
	if (in->del_s)
		ft_free_2d(in->del_s);
	if (in->del_str)
		ft_free_2d(in->del_str);
	if (in->input)
		free(in->input);
	if (in->out)
		ft_free_2d(in->out);
}
/*
void	init_raw(t_raw_in *in)
{
	in->del_s = NULL;
	in->del_str = NULL;
	in->input = NULL;
	in->n_hd = 0;
	in->n_pipe = 0;
	in->n_red = 0;
	in->n_words = 0;
	in->out = NULL;
	in->n_chd = 0;
	in->open_pipe = false;
}


int	main(void)
{
	//t_minishell_l	*lexed;
	t_raw_in		input;
	int				i;

	while (1)
	{
		i = -1;
		init_raw(&input);
		if (!get_line_cnc(&input))
			return (error("syntax error", 0));
		//lexed = lexer(&input);
		printf("hd:%d\nred:%d\npipe:%d\n", input.n_hd, input.n_red, input.n_pipe);
		while (++i < input.n_hd)
			printf("%d.%s\n%s", i + 1,  input.del_s[i], input.del_str[i]);
		free_raw(&input);
	}
}
*/