/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_line_cnc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbaumeis <lbaumeis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 19:25:32 by codespace         #+#    #+#             */
/*   Updated: 2024/10/11 20:09:39 by lbaumeis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// fix the del_str

void	get_hd(t_raw_in *in)
{
	in->del_str = (char **)ft_calloc(in->n_hd + 1, sizeof(char *));
	if (!in->del_str)
		return (exit_shell(NULL, NULL, in, "ALLOC FAILED"));
	if (in->n_hd)
	{
		sig_init(NULL, 1);
		while (in->n_chd < in->n_hd)
		{
			in->line = readline("> ");
			if (g_signal != 0 || !in->line)
			{
				free_raw(in);
				in->exit = 2;
				return ;
			}
			if (!ft_strcmp(in->del_s[in->n_chd], in->line))
			{
				in->n_chd++;
				free(in->line);
				continue ;
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
			return ((void)error("idk", 1));
		in->input = ft_strcat(in->input, in->line);
		set_first(in, in->line);
	}
}

int	is_bad(char *str)
{
	while (*str)
	{
		if (*str != ' ' && *str != '\t')
			return (0);
		str++;
	}
	return (1);
}

int	get_line_cnc(t_raw_in *in, t_pipex *p)
{
	char	*tmp;

	tmp = ft_strjoin_free_one(ft_strdup(p->pwd), "> ");
	if (isatty(fileno(stdin)))
		in->line = readline(tmp);
	else
	{
		char *line;
		line = get_next_line(fileno(stdin));
		in->line = ft_strtrim(line, "\n");
		free(line);
	}
	free(tmp);
	if (!in->line)
		return (in->exit = 1, 2);
	if (!ft_strlen(in->line) || is_bad(in->line))
		return (in->exit = 0, free(in->line), 2);
	add_history(in->line);
	set_op(in, in->line);
	if (!check_syntax(in->line) || in->open_pipe)
		return (0);
	in->input = ft_strcat(in->input, in->line);
	if (!in->input)
		return (free_raw(in), 2);
	set_first(in, in->line);
	free(in->line);
	in->line = NULL;
	if (in->n_hd)
		get_hd(in);
	if (in->exit == 2)
		return (2);
	return (1);
}
