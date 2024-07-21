/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbaumeis <lbaumeis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 06:41:58 by lbaumeis          #+#    #+#             */
/*   Updated: 2024/07/21 18:07:20 by lbaumeis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	check_filein(t_pipex *p)
{
	p->filein = open(p->av[1], O_RDONLY, 0644);
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
}

void	check_fileout(t_pipex *p)
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
void	init_p(t_pipex *p, int ac, char **av, char **envp)
{
	//p->av = p->m->str;
	p->av = av;
	p->filein = -1;
	p->hd = -1;
	p->fileout = -1;
	p->c = 0;
	here_or_not(ac, av, p, envp);
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

