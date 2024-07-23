/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   no_infile.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbaumeis <lbaumeis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 14:12:19 by lbaumeis          #+#    #+#             */
/*   Updated: 2024/07/23 18:38:49 by lbaumeis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

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

void	no_infile_exec(t_pipex *p, int *c)
{
	if (dup2(p->filein, STDIN_FILENO) == -1)
		err_free(p, 1);
	if (dup2(p->pip[*c][1], STDOUT_FILENO) == -1)
		err_free(p, 1);
	if (p->filein == -1)
		err_free(p, 1);
	close_pipes(p);
	exec_cmd(p);
	err_free(p, 1);
}

void	get_cur_cwd(t_pipex *p)
{
	p->cwd = getcwd(p->cwd, 0);
	if (p->cwd == NULL)
		err_free(p, 1);
	if (access(p->cwd, R_OK) == -1)
		err_free(p, 1);
}

void	read_cwd(t_pipex *p)
{
	DIR				*dir;
	struct dirent	*dir_content;

	get_cur_cwd(p);
	p->filein = open("cur_dir_cont", O_CREAT, O_RDONLY, 0644);
	if (p->filein == -1)
		err_free(p, 1);
	dir = opendir(p->cwd);
	if (dir == NULL)
		err_free(p, 1);
	dir_content = readdir(dir);
	while (dir_content)
	{
		ft_putstr_fd(dir_content->d_name, p->filein);
		dir_content = NULL;
		dir_content = readdir(dir);
	}
	if (closedir(dir) == -1)
		err_free(p, 1);
}
