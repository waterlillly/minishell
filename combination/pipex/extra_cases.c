/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extra_cases.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbaumeis <lbaumeis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 14:12:19 by lbaumeis          #+#    #+#             */
/*   Updated: 2024/08/10 15:15:40 by lbaumeis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../exec.h"

/*
DIR *opendir(const char *name); (success: pointer to stream, err: NULL)
struct dirent *readdir(DIR *dirp); DO NOT FREE!!
->  If  the  end  of  the  directory  stream   is
       reached,  NULL  is  returned and errno is not
       changed.  If an error  occurs,  NULL  is  re‐
       turned  and  errno  is set appropriately.  To
       distinguish end of stream from an error,  set
       errno  to  zero  before calling readdir() and
       then check the value of errno if NULL is  re‐
       turned.
int closedir(DIR *dirp); (success: 0, err: -1)
*/

void	single_exec(t_pipex *p)
{
	if (!p->cwd)
	{
		if (p->here == true)
		{
			p->filein = open("hd", O_RDONLY);
			if (p->filein == -1 || access("hd", R_OK) == -1)
				error(p, "hd", p->status);
		}
		if (dup2(p->filein, STDIN_FILENO) == -1)
			error(p, "dup2 failed", p->status);
	}
	if (p->out == true)
	{
		if (dup2(p->fileout, STDOUT_FILENO) == -1)
			error(p, "dup2 failed", p->status);
	}
	if (p->here)
		unlink("hd");
	if (p->filein && p->filein != STDIN_FILENO && p->filein != -1)
		close(p->filein);
	if (p->fileout && p->fileout != STDOUT_FILENO && p->fileout != -1)
		close(p->fileout);
	if (exec_cmd(p) < 0)
		error(p, "exec_cmd failed", p->status);
}

void	no_infile_exec(t_pipex *p, int *c)
{
	if (dup2(p->pip[*c][1], STDOUT_FILENO) == -1)
		error(p, "dup2 failed", p->status);
	close_pipes(p);
	if (exec_cmd(p) < 0)
		error(p, "exec_cmd failed", p->status);
}

/*
void	read_cwd(t_pipex *p)
{
	DIR				*dir;
	struct dirent	*dir_content;

	get_cur_cwd(p);
	if (access(p->cwd, R_OK) == -1)
		err_free(p, 1);
	p->filein = open("cur_dir_cont", O_CREAT | O_RDWR | O_TRUNC, 0666);
	if (p->filein == -1 || access("cur_dir_cont", W_OK) == -1
		|| access("cur_dir_cont", R_OK) == -1)
		err_free(p, 1);
	dir = opendir(p->cwd);
	if (dir == NULL)
		err_free(p, 1);
	dir_content = readdir(dir);
	while (dir_content)
	{
		ft_putstr_fd(dir_content->d_name, p->filein);
		ft_putchar_fd('\n', p->filein);
		dir_content = readdir(dir);
	}
	if (closedir(dir) == -1)
		err_free(p, 1);
}
*/