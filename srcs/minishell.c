#include <stdio.h>
#include "./libft/libft.h"
#include "minishell.h"
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

int error(char *str, int code)
{
	ft_putendl_fd(str, 1);
	exit (code);
	return 1;
}

void	remove_q(t_raw_in *in)
{
	int		i;
	char	*tmp;

	i = -1;
	while (++i < in->n_hd)
	{
		if (*in->del_s[i] == '\'' || *in->del_s[i] == '\"')
		{
			tmp = ft_substr(in->del_s[i], 1, ft_strlen(in->del_s[i]) - 2);
			free(in->del_s[i]);
			in->del_s[i] = tmp;
		}
	}
}

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

int	double_count(char *input)
{
	int	i;
	int	single_q;

	i = 0;
	single_q = 0;
	while (*input)
	{
		if (*input == '\'' && i % 2 == 0)
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
		if (*input == '\"' && i % 2 == 0)
			double_q++;
		if (*input == '\'' && double_q % 2 == 0)
			i++;
		input++;
	}
	return (i);
}

int open_quotes(char *input)
{
	int	single_q;
	int	double_q;

	single_q = single_count(input);
	double_q = double_count(input);
	if (single_q % 2 || double_q % 2)
		return (0);
	return (1);
}

int	open_line(char *input)
{
	if (!input || !*input)
		return (1);
	if (open_quotes(input))
		return (1);
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
	//in->del_s = ft_calloc((in->n_hd + 1), sizeof(char *));  // needs to be fixed for realloc
	while (i < in->n_hd - 1&& *line && *(line + 1))
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

int	check_pipe(char *str)
{
	int i;

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
	//in->del_str = ft_calloc((in->n_hd + 1), sizeof(char *));
	if (in->n_hd)
	{
		while (in->n_chd < in->n_hd)
		{
			ft_putstr_fd("heredoc>", 1);
			get_next_line(0, in->line);
			if (!ft_strcmp(in->del_s[in->n_chd], in->line[0]))
			{
				in->n_chd++;
				continue;
			}
			in->del_str[in->n_chd] = ft_strcat(in->del_str[in->n_chd], in->line[0]);
			in->del_str[in->n_chd] = ft_strcat(in->del_str[in->n_chd], "\n");
			free(in->line[0]);
		}
	}
}

void	get_pipe(t_raw_in *in)
{
	if (in->open_pipe)
	{
		ft_putstr_fd("command>", 1);
		get_next_line(0, in->line);
		if (!check_syntax(in->line[0]))
			return ((void)error("idk", 1));
		in->input = ft_strcat(in->input, in->line[0]);
		set_first(in, in->line[0]);
	}
}

int	get_line_cnc(t_raw_in *in)
{
	ft_putstr_fd("this is a legit minishell $>", 1);
	get_next_line(0, in->line);
	if (!check_syntax(in->line[0]))
		return (0);
	in->input = ft_strcat(in->input, in->line[0]);
	set_first(in, in->line[0]);
	free(in->line[0]);
	while (in->open_pipe || in->n_chd < in->n_hd)
	{
		get_hd(in);
		get_pipe(in);
	}
	return (1);
}

void	init_raw(t_raw_in *in)
{
	//in->del_s = NULL;
	//in->del_str = NULL;
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
		printf("hd:%d\nred:%d\npipe:%d\n", input.n_hd, input.n_red, input.n_pipe);
		while (++i < input.n_hd)
			printf("%d.%s\n%s", i + 1,  input.del_s[i], input.del_str[i]);
	}
}