/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbaumeis <lbaumeis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 14:55:29 by lbaumeis          #+#    #+#             */
/*   Updated: 2024/08/07 17:29:45 by lbaumeis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../exec.h"

// signal_reset
// {
// 	if (g_sig = SIGINT)
// 		errno_code = 130;
// 	if (g_sig = SIgQUIT)
// 		errno_code = 131;
// 	g_sig = 0;	
// }

// int heredoc(t_pipex *p)
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

void	get_cur_cwd(t_pipex *p)
{	
	p->cwd = get_env(p, "PWD");
	if (!p->cwd)
		error(p, "get_env failed", p->status);
	if (access(p->cwd, R_OK) == -1)
	{
		free(p->cwd);
		p->cwd = NULL;
		error(p, "no access", p->status);
	}
}

void	first_heredoc(t_pipex *p)
{
	char	*line;
	
	line = NULL;
	p->filein = -1;
	p->fileout = -1;
	p->filein = open("hd", O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (p->filein == -1 || access("hd", R_OK) == -1 || access("hd", W_OK) == -1)
		error(p, "hd", p->status);
	line = readline("> ");
	while (line && !ft_strcmp(line, p->delimiter))
	{
		ft_putstr_fd(line, p->filein);
		ft_putchar_fd('\n', p->filein);
		free(line);
		line = NULL;
		line = readline("> ");
	}
	close_all(p);
}

void	adjust_struct(t_pipex *p)
{
	if (p->in == true)
	{
		p->x = 2;
		if (p->out == true)
			p->cmd_count = p->ac - 3;
		else
			p->cmd_count = p->ac - 2;
	}
	else if (p->in == false)
	{
		get_cur_cwd(p);
		if (!p->cwd)
			error(p, "get_cur_cwd failed", p->status);
		p->x = 1;
		if (p->out == true)
			p->cmd_count = p->ac - 2;
		else
			p->cmd_count = p->ac - 1;
	}
}

void	adjust_struct_here(t_pipex *p)
{
	if (p->in == false)
	{
		p->x = 3;
		if (p->out == true && p->ac > 3)
			p->cmd_count = p->ac - 4;
		else
			p->cmd_count = p->ac - 3;
	}
	else
		error(p, "error", p->status);
}

void	here_or_not(t_pipex *p)
{
	//p->alot = false;
	if (!ft_strcmp(p->av[1], "here_doc"))
	{
		p->delimiter = NULL;
		p->here = false;
		adjust_struct(p);
		check_filein(p);
	}
	else
	{
		p->delimiter = p->av[2];
		p->here = true;
		adjust_struct_here(p);
		first_heredoc(p);
	}
	//if (p->cmd_count > 512)
		//p->alot = true;
}
