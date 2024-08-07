/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extra_cases.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbaumeis <lbaumeis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 14:12:19 by lbaumeis          #+#    #+#             */
/*   Updated: 2024/08/07 14:16:06 by lbaumeis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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

void	single_exec(t_ms *ms)
{
	ms->e->filein = -1;
	ms->e->fileout = -1;
	if (!ms->e->cwd)
	{
		if (ms->e->here == true)
		{
			ms->e->filein = open("hd", O_RDONLY);
			if (ms->e->filein == -1 || access("hd", R_OK) == -1)
				error(ms, "ms->e->filein", 1);
		}
		if (dup2(ms->e->filein, STDIN_FILENO) == -1)
			error(ms, "dup2 failed", 1);
	}
	if (ms->e->out == true)
	{
		if (dup2(ms->e->fileout, STDOUT_FILENO) == -1)
			error(ms, "dup2 failed", 1);
	}
	if (ms->e->here)
		unlink("hd");
	if (ms->e->filein && ms->e->filein != STDIN_FILENO && ms->e->filein != -1)
		close(ms->e->filein);
	if (ms->e->fileout && ms->e->fileout != STDOUT_FILENO && ms->e->fileout != -1)
		close(ms->e->fileout);
	exec_cmd(ms);
	error(ms, "exec_cmd failed", 1);
}

void	no_infile_exec(t_ms *ms, int *c)
{
	if (dup2(ms->e->pip[*c][1], STDOUT_FILENO) == -1)
		error(ms, "dup2 failed", 1);
	close_pipes(ms);
	exec_cmd(ms);
	error(ms, "exec_cmd failed", 1);
}

/*
void	read_cwd(t_ms *ms)
{
	DIR				*dir;
	struct dirent	*dir_content;

	get_cur_cwd(p);
	if (access(ms->e->cwd, R_OK) == -1)
		error(ms, NULL, 1);
	ms->e->filein = open("cur_dir_cont", O_CREAT | O_RDWR | O_TRUNC, 0666);
	if (ms->e->filein == -1 || access("cur_dir_cont", W_OK) == -1
		|| access("cur_dir_cont", R_OK) == -1)
		error(ms, NULL, 1);
	dir = opendir(ms->e->cwd);
	if (dir == NULL)
		error(ms, NULL, 1);
	dir_content = readdir(dir);
	while (dir_content)
	{
		ft_putstr_fd(dir_content->d_name, ms->e->filein);
		ft_putchar_fd('\n', ms->e->filein);
		dir_content = readdir(dir);
	}
	if (closedir(dir) == -1)
		error(ms, NULL, 1);
}
*/