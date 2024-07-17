/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbaumeis <lbaumeis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 06:41:29 by lbaumeis          #+#    #+#             */
/*   Updated: 2024/07/17 18:11:58 by lbaumeis         ###   ########.fr       */
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

/*ERROR*/
void	close_pipes(t_pipex *p);
void	close_all(t_pipex *p);
void	free_double(char **str);
void	err_free_two(t_pipex *p);
void	err_free(t_pipex *p, int exit_status);

/*INIT*/
int		check_filein(t_pipex *p);
int		check_fileout(t_pipex *p);
void 	init_pipes(t_pipex *p);
void	create_pipes(t_pipex *p);
void	init_p(t_pipex *p, int ac, char **av);


/*PROCESSES*/
void	first(t_pipex *p, char **envp);
void	middle(t_pipex *p, char **envp);
void	last(t_pipex *p, char **envp);
void	do_child(t_pipex *p, char **envp);

/*PIX*/
void 	close_all(t_pipex *p);
void	processes(t_pipex *p, char **envp);
void	wait_for_processes(t_pipex *p);

#endif
