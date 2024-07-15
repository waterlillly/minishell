/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_free_close.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbaumeis <lbaumeis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 06:41:58 by lbaumeis          #+#    #+#             */
/*   Updated: 2024/07/15 19:17:57 by lbaumeis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	wait_for_processes(t_pipex *p)
{
	int	i;

	i = 0;
	while (i < p->cmd_count)
	{
		if (waitpid(p->pid[i], &p->status, 0) == -1)
			err_free(p, 1);
		if (WIFEXITED(p->status))
			p->status = WEXITSTATUS(p->status);
		i++;
	}
}

void	init_p(t_pipex *p, int ac, char **av)
{
	int	i;

	i = 0;
	p->av = av;
	p->filein = check_filein(av, p);
	p->fileout = check_fileout(av, p);
	p->cmd_count = ac - 3;
	p->c = 0;
	p->x = 2;
	p->pid = malloc(sizeof(pid_t) * p->cmd_count);
	if (!p->pid)
		err_free(p, 1);
	p->pip = malloc(sizeof(int *) * p->cmd_count);
	if (!p->pip[2])
		err_free(p, 1);
	while (i < p->cmd_count)
	{
		p->pip[i] = malloc(sizeof(int) * 2);
		if (!p->pip[i])
			err_free(p, 1);
		i++;
	}
}

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

void	close_file(int file)
{
	if (file && file != STDIN_FILENO && file != STDOUT_FILENO && file != -1)
		close(file);
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
void	free_double(char **str)
{
	int	i;

	i = 0;
	if (!str)
		return ;
	while (str[i])
	{
		free(str[i]);
		i++;
	}
	free(str);
	str = NULL;
}

void	err_free(t_pipex *p, int exit_status)
{
	if (p->pid)
		close_pipes(p);
	if (p->pid)
		free(p->pid);
	if (p->filein && p->filein != STDIN_FILENO && p->filein != -1)
		close(p->filein);
	if (p->fileout && p->fileout != STDOUT_FILENO && p->fileout != -1)
		close(p->fileout);
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
/*
void	check_file(int i, char **av, t_pipex *p)
{
	if (i == p->cmd_count + 2)
		p->file = open(av[i], O_RDWR | O_CREAT | O_TRUNC, 0644);
	else
		p->file = open(av[i], O_RDONLY);
	if (p->file == -1)
	{
		perror(av[i]);
		err_free(p, 1);
	}
	if (i == p->cmd_count + 2 && (access(av[i], W_OK) == -1)
		&& (access(av[i], R_OK) == -1))
	{
		perror(av[i]);
		err_free(p, 1);
	}
	else if (i != p->cmd_count + 2 && (access(av[i], F_OK) == -1))
	{
		perror(av[i]);
		err_free(p, 1);
	}
	close(p->file);
}
*/
int	check_filein(char **av, t_pipex *p)
{
	p->filein = open(av[1], O_RDONLY);
	if (p->filein == -1)
	{
		perror(av[1]);
		err_free(p, 1);
	}
	if (access(av[1], F_OK) == -1)
	{
		perror(av[1]);
		err_free(p, 1);
	}
	return (p->filein);
}

int	check_fileout(char **av, t_pipex *p)
{
	p->fileout = open(av[p->cmd_count + 3], O_WRONLY | O_CREAT | O_TRUNC, 0777);
	if (p->fileout == -1)
	{
		perror(av[p->cmd_count + 3]);//
		err_free(p, 1);
	}
	if (access(av[p->cmd_count + 3], W_OK) == -1)
	{
		perror(av[p->cmd_count + 3]);
		err_free(p, 1);
	}
	return (p->fileout);
}
