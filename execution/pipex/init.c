/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbaumeis <lbaumeis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 06:41:58 by lbaumeis          #+#    #+#             */
/*   Updated: 2024/07/22 18:42:31 by lbaumeis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
/*
void	temp_file(t_pipex *p)
{
	p->temp = open("temp", O_RDWR, 0644);
	if (p->temp == -1 || access("temp", F_OK) == -1)
	{
		perror("temp");
		err_free(p, 1);
	}
}
*/
void	check_filein(t_pipex *p)
{
	char	*str;

	str = NULL;
	if (p->delimiter)
	{
		p->filein = open("hd", O_CREAT | O_RDWR, 0644);
		str = ft_strdup("hd");
	}
	else
	{
		p->filein = open(p->av[1], O_RDONLY, 0644);
		str = p->av[1];
	}
	if (p->filein == -1 || access(str, F_OK) == -1)
	{
		perror(str);
		err_free(p, 1);
	}
}

void	check_fileout(t_pipex *p)
{
	int	x;

	x = 0;
	if (p->delimiter)
		x = p->cmd_count + 3;
	else
		x = p->cmd_count + 2;
	p->fileout = open(p->av[x], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (p->fileout == -1 || access(p->av[x], W_OK) == -1)
	{
		perror(p->av[x]);
		err_free(p, 1);
	}
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
        p->pip[i] = malloc(sizeof(int) * 2);
        if (pipe(p->pip[i]) == -1)
		{
            perror("pipe");
            exit(EXIT_FAILURE);
        }
		i++;
    }
}

void	create_pipes(t_pipex *p)
{
	int	i;

	i = 0;
	while (i < p->cmd_count)
	{
		if (pipe(p->pip[i]) == -1)
			err_free(p, 1);
		i++;
	}
}
/*
void	check_in(t_pipex *p)
{
	if (p->m->infile)
	{
		p->filein = open(p->m->infile, O_RDONLY, 0644);
		if (p->filein == -1)
		{
			perror(p->av[1]);
			err_free(p, 1);
		}
		if (access(p->m->infile, F_OK) == -1)
		{
			perror(p->m->infile);
			err_free(p, 1);
		}
	}
}

void	check_out(t_pipex *p)
{
	if (p->m->out == false)//need an outfile!
	{
		p->fileout = open(p->m->outfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (p->fileout == -1)
		{
			perror(p->m->outfile);
			err_free(p, 1);
		}
		if (access(p->m->outfile, W_OK) == -1)
		{
			perror(p->m->outfile);
			err_free(p, 1);
		}
	}
}
*/
void	init_p(t_pipex *p)
{
	p->filein = -1;
	p->fileout = -1;
	p->copy_stdout = dup(STDOUT_FILENO);
	//p->temp = -1;
	//add check for in and out
	p->in = true;
	p->out = true;
	here_or_not(p);
	if (p->out == true)
	//check_out(p);
		check_fileout(p);
	p->status = 0;
	p->pid = NULL;
	p->args = NULL;
	p->paths = NULL;
	p->path = NULL;
	p->executable = NULL;
	p->part = NULL;
	p->cmd = NULL;
	p->pid = malloc(sizeof(pid_t) * p->cmd_count);
	if (!p->pid)
		err_free(p, 1);
	p->pip = NULL;
	init_pipes(p);
}

