/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbaumeis <lbaumeis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 18:04:36 by lbaumeis          #+#    #+#             */
/*   Updated: 2024/08/19 12:56:20 by lbaumeis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	close_pipes(t_pipex *p)
{
	int	i;

	i = 0;
	if (p->cmd_count <= 1)
		return ;
	else if (p && p->pip && p->pip[i])
	{
		while (p->pip && i < p->cmd_count - 1 && p->pip[i])
		{
			if (p->pip[i][0] && p->pip[i][0] != -1 && p->pip[i][0] != STDIN_FILENO)
				close(p->pip[i][0]);
			if (p->pip[i][1] && p->pip[i][1] != -1 && p->pip[i][1] != STDOUT_FILENO)
				close(p->pip[i][1]);
			free(p->pip[i]);
			//p->pip[i] = 0;
			i++;
		}
		free(p->pip);
		//p->pip = 0;
	}
}

void	close_all(t_pipex *p)
{
	int	x;

	x = 3;
	while (p && x < 1024)
	{
		if (x != p->filein && x != p->fileout)
			close(x);
		x++;
	}
	if (p && p->filein && p->filein != STDIN_FILENO && p->filein != -1)
		close(p->filein);
	if (p && p->fileout && p->fileout != STDOUT_FILENO && p->fileout != -1)
		close(p->fileout);
	//reset_fds(p);
	if (p && p->copy_stdout && p->copy_stdout != STDOUT_FILENO && p->copy_stdout != -1)
		close(p->copy_stdout);
	//if (p && p->copy_stdin && p->copy_stdin != STDIN_FILENO && p->copy_stdin != -1)
	//	close(p->copy_stdin);
	if (p && p->here)
		unlink("hd");
	if (p && p->pip)
		close_pipes(p);
}

void	free_double(char **str)
{
	int	i;

	i = 0;
	if (!str || !str[i])
		return ;
	while (str[i])
	{
		free(str[i]);
		str[i] = NULL;
		i++;
	}
	//free(str);
	str = NULL;
}

void	err_free_two(t_pipex *p)
{
	if (p->pid)
	{
		free(p->pid);
		p->pid = NULL;
	}
	if (p->pip || p->copy_stdout)//|| p->copy_stdin
		close_all(p);
	//if (p->paths)
	//{
	//	free_double(p->paths);
	//	p->paths = NULL;
	//}
}

void	err_free(t_pipex *p)
{
	err_free_two(p);
	if (p->path)
	{
		free(p->path);
		p->path = NULL;
	}
	if (p->executable)
	{
		free(p->executable);
		p->executable = NULL;
	}
	if (p->part)
	{
		free(p->part);
		p->part = NULL;
	}
}
