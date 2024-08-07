/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbaumeis <lbaumeis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 14:55:29 by lbaumeis          #+#    #+#             */
/*   Updated: 2024/08/07 14:22:58 by lbaumeis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// signal_reset
// {
// 	if (g_sig = SIGINT)
// 		errno_code = 130;
// 	if (g_sig = SIgQUIT)
// 		errno_code = 131;
// 	g_sig = 0;	
// }

// int heredoc(t_ms *ms)
// {
// 	if (g_sig != 0)
// 	{
// 		reset_signal(mini, g_sig)
// 	}
// 	while (1)
// 	{
// 		if (first_heredoc(p) == 1)
// 			break;
// 	}
// }

void	get_cur_cwd(t_ms *ms)
{	
	ms->e->cwd = get_env(ms, "PWD");
	if (!ms->e->cwd)
		error(ms, "get_env failed", 1);
	if (access(ms->e->cwd, R_OK) == -1)
	{
		free(ms->e->cwd);
		ms->e->cwd = NULL;
		error(ms, "no access", 1);
	}
}

void	first_heredoc(t_ms *ms)
{
	char	*line;
	
	line = NULL;
	ms->e->filein = -1;
	ms->e->fileout = -1;
	ms->e->filein = open("hd", O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (ms->e->filein == -1 || access("hd", R_OK) == -1 || access("hd", W_OK) == -1)
		error(ms, "hd", 1);
	line = readline("> ");
	while (line && !ft_strcmp(line, ms->e->delimiter))
	{
		ft_putstr_fd(line, ms->e->filein);
		ft_putchar_fd('\n', ms->e->filein);
		free(line);
		line = NULL;
		line = readline("> ");
	}
	close_all(ms);
}

void	adjust_struct(t_ms *ms)
{
	if (ms->e->in == true)
	{
		ms->e->x = 2;
		if (ms->e->out == true)
			ms->e->cmd_count = ms->e->ac - 3;
		else
			ms->e->cmd_count = ms->e->ac - 2;
	}
	else if (ms->e->in == false)
	{
		get_cur_cwd(ms);
		if (!ms->e->cwd)
			error(ms, "no cwd", 1);
		ms->e->x = 1;
		if (ms->e->out == true)
			ms->e->cmd_count = ms->e->ac - 2;
		else
			ms->e->cmd_count = ms->e->ac - 1;
	}
}

void	adjust_struct_here(t_ms *ms)
{
	if (ms->e->in == false)
	{
		ms->e->x = 3;
		if (ms->e->out == true && ms->e->ac > 3)
			ms->e->cmd_count = ms->e->ac - 4;
		else
			ms->e->cmd_count = ms->e->ac - 3;
	}
	else
		error(ms, NULL, 1);
}

void	here_or_not(t_ms *ms)
{
	//ms->e->alot = false;
	if (!ft_strcmp(ms->e->av[1], "here_doc"))
	{
		ms->e->delimiter = NULL;
		ms->e->here = false;
		adjust_struct(ms);
		check_filein(ms);
	}
	else
	{
		ms->e->delimiter = ms->e->av[2];
		ms->e->here = true;
		adjust_struct_here(ms);
		first_heredoc(ms);
	}
	//if (ms->e->cmd_count > 512)
		//ms->e->alot = true;
}
