/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close_free.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbaumeis <lbaumeis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 18:04:36 by lbaumeis          #+#    #+#             */
/*   Updated: 2024/08/07 13:21:30 by lbaumeis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	close_pipes(t_ms *ms)
{
	int	i;

	i = ms->e->cmd_count - 1;
	while (i >= 0)
	{
		if (ms->e->pip[i][0] && ms->e->pip[i][0] != -1 && ms->e->pip[i][0] != STDIN_FILENO)
			close(ms->e->pip[i][0]);
		if (ms->e->pip[i][1] && ms->e->pip[i][1] != -1 && ms->e->pip[i][0] != STDOUT_FILENO)
			close(ms->e->pip[i][1]);
		free(ms->e->pip[i]);
		ms->e->pip[i] = NULL;
		i--;
	}
	free(ms->e->pip);
	ms->e->pip = NULL;
}

void	close_all(t_ms *ms)
{
	if (ms->e->filein && ms->e->filein != STDIN_FILENO && ms->e->filein != -1)
		close(ms->e->filein);
	if (ms->e->fileout && ms->e->fileout != STDOUT_FILENO && ms->e->fileout != -1)
		close(ms->e->fileout);
	if (ms->e->copy_stdout && ms->e->copy_stdout != STDOUT_FILENO && ms->e->copy_stdout != -1)
		close(ms->e->copy_stdout);
	close_pipes(ms);
}

void	free_double(char **str)
{
	int	i;

	i = 0;
	if (!str)
		return ;
	while (str[i])
	{
		free(str[i]);
		str[i] = NULL;
		i++;
	}
	free(str);
	str = NULL;
}

void	err_free_two(t_ms *ms)
{
	if (ms->e->pid)
	{
		free(ms->e->pid);
		ms->e->pid = NULL;
	}
	if (ms->e->pip || ms->e->copy_stdout)
		close_all(ms);
	if (ms->e->args)
	{
		free_double(ms->e->args);
		ms->e->args = NULL;
	}
	if (ms->e->paths)
	{
		free_double(ms->e->paths);
		ms->e->paths = NULL;
	}
}

void	err_free(t_ms *ms)
{
	err_free_two(ms);
	if (ms->e->path)
	{
		free(ms->e->path);
		ms->e->path = NULL;
	}
	if (ms->e->executable)
	{
		free(ms->e->executable);
		ms->e->executable = NULL;
	}
	if (ms->e->part)
	{
		free(ms->e->part);
		ms->e->part = NULL;
	}
	if (ms->e->here)
		unlink("hd");
	err_free_buildins(ms);
}
