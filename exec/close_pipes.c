/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbaumeis <lbaumeis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 18:04:36 by lbaumeis          #+#    #+#             */
/*   Updated: 2024/10/05 14:15:59 by lbaumeis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	closing(t_pipex *p)
{
	int	i;

	i = 0;
	if (!p)
		return ;
	if (p && p->filein != -1 && p->filein != STDIN_FILENO)
		close(p->filein);
	if (p && p->fileout != -1 && p->fileout != STDOUT_FILENO)
		close(p->fileout);
	if (p && p->pip && p->pip[i])
	{
		while (i < p->cmd_count && p->pip[i])
		{
			if (p->pip[i][0] && p->pip[i][0] != -1 && p->pip[i][0] != STDIN_FILENO)
				close(p->pip[i][0]);
			if (p->pip[i][1] && p->pip[i][1] != -1 && p->pip[i][1] != STDOUT_FILENO)
				close(p->pip[i][1]);
			i++;
		}
	}
}

void	close_pipes(t_pipex *p)
{
	int	i;

	i = 0;
	if (!p)
		return ;
	else if (p && p->pip && p->pip[i])
	{
		while (i < p->cmd_count && p->pip[i])
		{
			if (p->pip[i][0] && p->pip[i][0] != -1 && p->pip[i][0] != STDIN_FILENO)
				close(p->pip[i][0]);
			if (p->pip[i][1] && p->pip[i][1] != -1 && p->pip[i][1] != STDOUT_FILENO)
				close(p->pip[i][1]);
			free(p->pip[i]);
			i++;
		}
		free(p->pip);
		p->pip = 0;
	}
}

void	close_all(t_pipex *p)
{
	if (p && p->filein != -1 && p->filein != STDIN_FILENO)
		close(p->filein);
	if (p && p->fileout != -1 && p->fileout != STDOUT_FILENO)
		close(p->fileout);
	if (p && p->pip)
		close_pipes(p);
}
