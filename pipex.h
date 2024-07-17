/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbaumeis <lbaumeis@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 06:41:29 by lbaumeis          #+#    #+#             */
/*   Updated: 2024/07/17 13:07:14 by lbaumeis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "libft/libft.h"
# include <sys/wait.h>
# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <stdio.h>
# include <fcntl.h>
# include <errno.h>

typedef struct s_pipex
{
	pid_t	*pid;
	int		**pip;
	char	**av;
	int		c;
	int		x;
	int		filein;
	int		fileout;
	int		status;
	int		cmd_count;
	char	**args;
	char	**paths;
	char	*path;
	char	*executable;
	char	*part;
	char	*cmd;
}			t_pipex;

/*PIPEX*/
void	find_path(t_pipex *p, char **envp);
char	*is_exec(t_pipex *p);
void	exec_cmd(char **av, int x, t_pipex *p, char **envp);

/*CHECK_FREE_CLOSE*/
void 	init_pipes(t_pipex *p);
void	init_p(t_pipex *p, int ac, char **av);
void	close_pipe(int *pipe);
void	close_pipes(t_pipex *p);
void	close_file(int file);
void	err_free(t_pipex *p, int exit_status);
void	free_double(char **str);
void	free_double_int(int **str);
int		check_filein(t_pipex *p);
int		check_fileout(t_pipex *p);

/*PROCESSES*/
void	create_pipes(t_pipex *p);
void	first(t_pipex *p, char **envp);
void	middle(t_pipex *p, char **envp);
void	last(t_pipex *p, char **envp);

/*PIX*/
void 	close_all(t_pipex *p);
void	do_child(t_pipex *p, char **envp);
void	do_last(t_pipex *p, char **envp);
void	decide(t_pipex *p);
void	processes(t_pipex *p, char **envp);
void	wait_for_processes(t_pipex *p);
//void	do_child(t_pipex *p, int *pipe_fd, int filein_fd, char **envp);
//void	do_else(t_pipex *p, int *pipe_fd, int filein_fd);
//void	start(t_pipex *p, char **envp);

#endif
