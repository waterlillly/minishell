/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extra_cases.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbaumeis <lbaumeis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 14:12:19 by lbaumeis          #+#    #+#             */
/*   Updated: 2024/08/16 17:05:55 by lbaumeis         ###   ########.fr       */
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

void	single_exec(t_pipex *p, t_minishell_p *pars)
{
	if (p && p->here == true)
	{
		p->filein = open("hd", O_RDONLY);
		if (p->filein == -1 || access("hd", R_OK) == -1)
			return ;//error(p, "hd", p->status);
		if (dup2(p->filein, STDIN_FILENO) == -1)
			return ;//error(p, "dup2 failed", p->status);
	}
	else if (p && pars && pars->infile)
	{
		check_filein(p, pars);
		if (dup2(p->filein, STDIN_FILENO) == -1)
			return ;//error(p, "dup2 failed", p->status);
	}
	if (p && pars && pars->outfile)
	{
		check_fileout(p, pars);
		if (dup2(p->fileout, STDOUT_FILENO) == -1)
			return ;//error(p, "dup2 failed", p->status);
	}
	close_all(p);
	if (exec_cmd(p, pars) < 0)
		return ;//error(p, "exec_cmd failed", p->status);
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