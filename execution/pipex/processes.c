/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   processes.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbaumeis <lbaumeis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 06:41:51 by lbaumeis          #+#    #+#             */
/*   Updated: 2024/07/22 18:42:36 by lbaumeis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
/*
void	output_temp(t_pipex *p)
{
	char	*line;
	
	line = NULL;
	if (p->temp)
	{
		line = get_next_line(p->temp);
		while (line)
		{
			ft_printf("%s", line);
			free(line);
			line = NULL;
			line = get_next_line(p->temp);
		}
		close(p->temp);
	}
}
*/

void	first(t_pipex *p, int *c)
{
	if (dup2(p->filein, STDIN_FILENO) == -1)
		err_free(p, 1);
	if (dup2(p->pip[*c][1], STDOUT_FILENO) == -1)
		err_free(p, 1);
	close_pipes(p);
	exec_cmd(p);
	err_free(p, 1);
}
/*
void	first(t_pipex *p)
{
	if (p->m->infile)
	{
		if (dup2(p->filein, STDIN_FILENO) == -1)
			err_free(p, 1);
	}
	if (dup2(p->pip[p->c][1], STDOUT_FILENO) == -1)
		err_free(p, 1);
	close_pipes(p);
	exec_cmd(p);
	err_free(p, 1);
}
*/

void	middle(t_pipex *p, int *c)
{
	if (dup2(p->pip[*c - 1][0], STDIN_FILENO) == -1)
		err_free(p, 1);
	if (dup2(p->pip[*c][1], STDOUT_FILENO) == -1)
		err_free(p, 1);
	close_pipes(p);
	exec_cmd(p);
	err_free(p, 1);
}

void	last(t_pipex *p, int *c)
{
	if (dup2(p->pip[*c - 1][0], STDIN_FILENO) == -1)
		err_free(p, 1);
	if (p->out == true)
	{
		if (dup2(p->fileout, STDOUT_FILENO) == -1)
			err_free(p, 1);
	}
	else
	{
		if (dup2(STDOUT_FILENO, p->copy_stdout) == -1)
			err_free(p, 1);
		close(p->copy_stdout);
	}
	//else
	//{
	//	temp_file(p);
	//	if (dup2(p->temp, STDOUT_FILENO) == -1)
	//		err_free(p, 1);
	//}
	close_pipes(p);
	exec_cmd(p);
	err_free(p, 1);
}

/*
void	last(t_pipex *p)
{
	if (dup2(p->pip[p->c - 1][0], STDIN_FILENO) == -1)
		err_free(p, 1);
	if (p->m->std_out == false)
	{
		if (dup2(p->fileout, STDOUT_FILENO) == -1)
			err_free(p, 1);
	}
	close_pipes(p);
	exec_cmd(p);
	err_free(p, 1);
}
*/

void	do_child(t_pipex *p, int *c)
{
	if (*c == 0)
		first(p, c);
	else if (*c == p->cmd_count - 1)
		last(p, c);
	else
		middle(p, c);
}
