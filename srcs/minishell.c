#include <stdio.h>
#include "./libft/libft.h"
#include "../includes/minishell.h"
/*

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
*/

int	open_line(char *input)
{
	if (!input || !*input)
		return (1);
	if (open_quotes(input))
		return (1);
	return (0);
}


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
	in->n_lessalloc = 0;
	in->sum = 0;
}

void	print_parsed(t_minishell_p *in)
{
	int	i;
	t_minishell_l *tmp;
	while (in)
	{
		tmp = in->redirect;
		i = -1;
		while (in->str[++i])
			printf("str%d.:%s\n", i + 1, in->str[i]);
		if (tmp)
		{
			while (tmp)
			{
				printf("token:%d\nfile:%s\n", tmp->token, tmp->input);
				tmp = tmp->next;
			}
		}
		else
			printf("NULL\n");
		printf("\n***********\n");
		in = in->next;
	}
}

void free_parse(t_minishell_p *in)
{
	t_minishell_l	*tmp_l;
	t_minishell_p	*tmp_p;

	while (in)
	{
		tmp_p = in->next;
		while (in->redirect)
		{
			tmp_l = in->redirect->next;
			free (in->redirect);
			in->redirect = tmp_l;
		}
		if (in->str)
			free(in->str);
		free(in);
		in = tmp_p;
	}
}

int	main(void)
{
	t_minishell_l	*lexed;
	t_minishell_p	*parsed;
	t_raw_in		input;

	while (1)
	{
		ft_bzero(&input, sizeof(t_raw_in));
		init_raw(&input);
		if (!get_line_cnc(&input))
			return (error("syntax error", 0));
		//printf("%s\n", input.input);
		lexed = lexer(&input);
		parsed = parser(lexed, &input);
		print_parsed(parsed);
		free_raw(&input);
		free_parse(parsed);
	}
}
