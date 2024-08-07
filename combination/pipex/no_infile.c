/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   no_infile.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbaumeis <lbaumeis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 14:12:19 by lbaumeis          #+#    #+#             */
/*   Updated: 2024/08/07 18:01:50 by lbaumeis         ###   ########.fr       */
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

void	no_infile_exec(t_pipex *p, int *c)
{
	if (dup2(p->pip[*c][1], STDOUT_FILENO) == -1)
		error(p, "dup2 failed", p->status);
	close_pipes(p);
	exec_cmd(p);
	error(p, "exec_cmd failed", p->status);
}

void	get_cur_cwd(t_pipex *p)
{
	p->cwd = get_env(p, "PWD");
	if (p->cwd == NULL)
		error(p, "get_env failed", p->status);
	if (access(p->cwd, R_OK) == -1)
		error(p, "no access", p->status);
}
/*
void	read_cwd(t_pipex *p)
{
	DIR				*dir;
	struct dirent	*dir_content;

	get_cur_cwd(p);
	if (access(p->cwd, R_OK) == -1)
		error(p, "error", p->status);
	p->filein = open("cur_dir_cont", O_CREAT | O_RDWR | O_TRUNC, 0666);
	if (p->filein == -1 || access("cur_dir_cont", W_OK) == -1
		|| access("cur_dir_cont", R_OK) == -1)
		error(p, "error", p->status);
	dir = opendir(p->cwd);
	if (dir == NULL)
		error(p, "error", p->status);
	dir_content = readdir(dir);
	while (dir_content)
	{
		ft_putstr_fd(dir_content->d_name, p->filein);
		ft_putchar_fd('\n', p->filein);
		dir_content = readdir(dir);
	}
	if (closedir(dir) == -1)
		error(p, "error", p->status);
}
*/