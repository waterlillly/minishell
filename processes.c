/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   processes.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbaumeis <lbaumeis@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 06:41:51 by lbaumeis          #+#    #+#             */
/*   Updated: 2024/07/17 12:54:20 by lbaumeis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	first(t_pipex *p, char **envp)
{
	printf("CHILD: first\n");
	if (dup2(p->filein, STDIN_FILENO) == -1)
		err_free(p, 1);
	if (dup2(p->pip[p->c][1], STDOUT_FILENO) == -1)
		err_free(p, 1);
	close_pipe(p->pip[p->c]);
	exec_cmd(p->av, p->x, p, envp);
	err_free(p, 1);
}

void	middle(t_pipex *p, char **envp)
{
	printf("CHILD: middle\n");
	if (dup2(p->pip[p->c - 1][0], STDIN_FILENO) == -1)
		err_free(p, 1);
	if (dup2(p->pip[p->c][1], STDOUT_FILENO) == -1)
		err_free(p, 1);
	close_pipe(p->pip[p->c - 1]);
	close_pipe(p->pip[p->c]);
	exec_cmd(p->av, p->x, p, envp);
	err_free(p, 1);
}

void	last(t_pipex *p, char **envp)
{
	printf("CHILD: last\n");
	if (dup2(p->pip[p->c - 1][0], STDIN_FILENO) == -1)
		err_free(p, 1);
	if (dup2(p->fileout, STDOUT_FILENO) == -1)
		err_free(p, 1);
	close_pipe(p->pip[p->c - 1]);
	exec_cmd(p->av, p->x, p, envp);
	err_free(p, 1);
}

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

void	create_pipes(t_pipex *p)
{
	int	i;

	i = 0;
	while (i < p->cmd_count - 1)
	{
		if (pipe(p->pip[i]) == -1)
			err_free(p, 1);
		i++;
	}
}

/*
void	first_child(char **av, t_pipex *p, char **envp, int *pipe_a)
{
	check_filein(av, p);
	p->filein = open(av[1], O_RDONLY);
	if (p->filein == -1)
		err_free(p, pipe_a, 1);
	if (dup2(pipe_a[1], STDOUT_FILENO) == -1)
		err_free(p, pipe_a, 1);
	if (dup2(p->filein, STDIN_FILENO) == -1)
		err_free(p, pipe_a, 1);
	close_pipe(pipe_a);
	exec_cmd(av, p->x, p, envp);
}

void	next_child(char **av, t_pipex *p, char **envp, int *pipe_a)
{
	int		pipe_b[2];
	
	if (pipe(pipe_b) == -1)
		err_free(p, pipe_a, 1);
	p->c++;
	p->pid[p->c] = fork();
	if (p->pid[p->c] == -1)
		err_free(p, pipe_a, 1);
	else if (p->pid[p->c] == 0)
	{
		if (dup2(pipe_a[0], STDIN_FILENO) == -1)
			err_free(p, pipe_a, 1);
		if (dup2(pipe_b[1], STDOUT_FILENO) == -1)
			err_free(p, pipe_a, 1);
	}
	close_pipes(pipe_a, pipe_b);
	exec_cmd(av, p->x, p, envp);
}

void	last_child(char **av, t_pipex *p, char **envp, int *pipe_a)
{	
	check_fileout(av, p);
	p->fileout = open(av[4], O_WRONLY | O_CREAT | O_TRUNC, 0777);//if here_doc: O_RDWR | O_CREAT | O_APPEND 0644
	if (p->fileout == -1)
		err_free(p, pipe_a, NULL, 1);
	p->c++;
	p->pid[p->c] = fork();
	if (p->pid[p->c] == -1)
		err_free(p, pipe_a, NULL, 1);
	else if (p->pid[p->c] == 0)
	{
		if (dup2(pipe_a[0], STDIN_FILENO) == -1)
			err_free(p, pipe_a, NULL, 1);
		if (dup2(p->fileout, STDOUT_FILENO) == -1)
			err_free(p, pipe_a, NULL, 1);
		close_pipes(pipe_a, NULL);
		exec_cmd(av, p->x, p, envp);
	}
}

int	wait_for_processes(t_pipex *p)
{
	int	i;

	i = 0;
	while (i < p->cmd_count)//
	{
		if (waitpid(p->pid, &p->status, 0) == -1)
			err_free(p, p->pip, 1);
		if (WIFEXITED(p->status))
			p->status = WEXITSTATUS(p->status);
		i++;
	}
	return (p->status);
}

void	start(char **av, t_pipex *p, char **envp)
{
	int		pipe_a[2];
	int		pipe_fd;
	
	if (pipe(pipe_a) == -1)
		err_free(p, NULL, NULL, 1);
	pipe_fd = check_filein(av, p);
	pipe_a[0] = -1;
	pipe_a[1] = check_fileout(av, p);
	p->pid[p->c] = fork();
	if (p->pid[p->c] == -1)
		err_free(p, pipe_a, NULL, 1);
	else if (p->pid[p->c] == 0)
		first_child(av, p, envp, pipe_a);
	close_pipes(pipe_a, NULL);
	waitpid(0, NULL, 0);
	p->x++;
	while (p->x < p->cmd_count + 2)
	{
		if (p->x < p->cmd_count + 2)
			next_child(av, p, envp, pipe_a);
		else if (p->x == p->cmd_count + 2)
			last_child(av, p, envp, pipe_a);
		p->x++;
		waitpid(0, NULL, 0);
	}
}
*/