/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_free_close.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbaumeis <lbaumeis@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 06:41:58 by lbaumeis          #+#    #+#             */
/*   Updated: 2024/07/17 13:09:16 by lbaumeis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	close_pipe(int *pipe)
{
	if (pipe[0] && pipe[0] != STDIN_FILENO && pipe[0] != -1)
		close(pipe[0]);
	if (pipe[1] && pipe[1] != STDOUT_FILENO && pipe[1] != -1)
		close(pipe[1]);
}

void	close_pipes(t_pipex *p)
{
	int	i;

	i = 0;
	while (p->pip[i])
	{
		close_pipe(p->pip[i]);
		i++;
	}
}

void	close_all(t_pipex *p)
{
	if (p->filein && p->filein != STDIN_FILENO && p->filein != -1)
		close(p->filein);
	if (p->fileout && p->fileout != STDOUT_FILENO && p->fileout != -1)
		close(p->fileout);
	if (p->pip)
		close_pipes(p);
}

void init_pipes(t_pipex *p)
{
	int i;

	i = 0;
    p->pip = malloc(p->cmd_count * sizeof(int *));
	if (!p->pip)
		err_free(p, 1);
    while (i < p->cmd_count)
	{
        p->pip[i] = malloc(2 * sizeof(int));
        if (pipe(p->pip[i]) == -1)
		{
            perror("pipe");
            exit(EXIT_FAILURE);
        }
		i++;
    }
}

void	init_p(t_pipex *p, int ac, char **av)
{
	p->av = av;
	p->cmd_count = ac - 3;
	p->c = 0;
	p->x = 2;
	p->filein = check_filein(p);
	p->fileout = check_fileout(p);
	p->pid = malloc(sizeof(pid_t) * p->cmd_count);
	if (!p->pid)
		err_free(p, 1);
	init_pipes(p);
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

void	free_double_int(int **str)
{
	int	i;

	i = 0;
	if (!str)
		return ;
	while (str[i])
	{
		free(str[i]);
		str[i] = 0;
		i++;
	}
	free(str);
	str = 0;
}

void	err_free(t_pipex *p, int exit_status)
{
	close_all(p);
	if (p->pid)
		free(p->pid);
	if (p->pip)
		free_double_int(p->pip);
	if (p->args)
		free_double(p->args);
	if (p->paths)
		free_double(p->paths);
	if (p->path)
		free(p->path);
	if (p->executable)
		free(p->executable);
	if (p->part)
		free(p->part);
	exit(exit_status);
}

int	check_filein(t_pipex *p)
{
	p->filein = open(p->av[1], O_RDONLY);
	if (p->filein == -1)
	{
		perror(p->av[1]);
		err_free(p, 1);
	}
	if (access(p->av[1], F_OK) == -1)
	{
		perror(p->av[1]);
		err_free(p, 1);
	}
	return (p->filein);
}

int	check_fileout(t_pipex *p)
{
	p->fileout = open(p->av[p->cmd_count + 2], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (p->fileout == -1)
	{
		perror(p->av[p->cmd_count + 2]);
		err_free(p, 1);
	}
	if (access(p->av[p->cmd_count + 2], W_OK) == -1)
	{
		perror(p->av[p->cmd_count + 2]);
		err_free(p, 1);
	}
	return (p->fileout);
}

/*
void	close_fds(t_pipex *p)
{
	int	x;//

	x = 0;//
	while (x < p->cmd_count)//
	{
		if (p->fd[x][0] && p->fd[x][0] != -1)
			close(p->fd[x][0]);
		if (p->fd[x][1] && p->fd[x][1] != -1)
			close(p->fd[x][1]);
		x++;
	}
	if (p->filein && p->filein != STDIN_FILENO && p->filein != -1)
		close(p->filein);
	if (p->fileout && p->fileout != STDOUT_FILENO && p->fileout != -1)
		close(p->fileout);
}
*/