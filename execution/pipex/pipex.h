/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbaumeis <lbaumeis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 06:41:29 by lbaumeis          #+#    #+#             */
/*   Updated: 2024/07/25 15:59:30 by lbaumeis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1
# endif

# include <features.h>
# include <signal.h>
# include <sys/signal.h>
# include <term.h>
# include <dirent.h>
# include <sys/ioctl.h>
# include "../../libft/libft.h"
# include <sys/wait.h>
# include <stdlib.h>
# include <stddef.h>
# include <unistd.h>
# include <string.h>
# include <stdio.h>
# include <fcntl.h>
# include <errno.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <complex.h>
# include <stdbool.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <dirent.h>
# include "../../parsing/minishell.h"

typedef struct s_pipex
{
	pid_t	*pid;
	int		**pip;
	char	**av;
	char	**envp;
	char	*cwd;
	int		ac;
	int		x;//first cmd
	int		copy_stdout;
	int		filein;
	int		fileout;
	bool	in;
	bool	out;
	bool	here;
	int		status;
	int		cmd_count;
	char	*delimiter;
	char	**args;
	char	**paths;
	char	*path;
	char	*executable;
	char	*part;
	char	*cmd;
	t_minishell_p	*m;
}			t_pipex;

/*PIPEX*/
void	find_path(t_pipex *p);
char	*is_exec(t_pipex *p);
void	exec_cmd(t_pipex *p);

/*ERROR*/
void	close_pipes(t_pipex *p);
void	close_all(t_pipex *p);
void	free_double(char **str);
void	err_free_two(t_pipex *p);
void	err_free(t_pipex *p, int exit_status);

/*INIT*/
void	check_filein(t_pipex *p);
void	check_fileout(t_pipex *p);
void 	init_pipes(t_pipex *p);
void	init_p(t_pipex *p);
//void	check_in(t_pipex *p);
//void	check_out(t_pipex *p);

/*PROCESSES*/
void	first(t_pipex *p, int *c);
void	middle(t_pipex *p, int *c);
void	last(t_pipex *p, int *c);
void	do_child(t_pipex *p, int *c);

/*CHECK*/
int		check_empty(char **av);
void	check_args(t_pipex *p, int ac, char **av);

/*HERE_DOC*/
void	get_cur_cwd(t_pipex *p);
void	first_heredoc(t_pipex *p);
void	adjust_struct(t_pipex *p);
void	adjust_struct_here(t_pipex *p);
void	here_or_not(t_pipex *p);

/*EXTRA_CASES*/
void	single_exec(t_pipex *p);
void	no_infile_exec(t_pipex *p, int *c);
//void	read_cwd(t_pipex *p);

/*ENVP*/
void	get_envp(t_pipex *p);

#endif
