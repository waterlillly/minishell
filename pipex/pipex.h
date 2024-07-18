/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbaumeis <lbaumeis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 06:41:29 by lbaumeis          #+#    #+#             */
/*   Updated: 2024/07/18 20:24:58 by lbaumeis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1
# endif

# include "libft/libft.h"
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

typedef struct s_pipex
{
	pid_t	*pid;
	int		**pip;
	char	**av;
	int		c;
	int		x;
	int		hd;
	int		filein;
	int		fileout;
	int		status;
	int		cmd_count;
	char	*delimiter;
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
void	check_filein(t_pipex *p);
void	check_fileout(t_pipex *p);
void 	init_pipes(t_pipex *p);
void	create_pipes(t_pipex *p);
void	init_p(t_pipex *p, int ac, char **av, char **envp);

/*PROCESSES*/
void	first(t_pipex *p, char **envp);
void	middle(t_pipex *p, char **envp);
void	last(t_pipex *p, char **envp);
void	do_child(t_pipex *p, char **envp);

/*CHECK*/
void	ft_count_args(t_pipex *p, int ac, char **av);
int		check_empty(char **av);
void	check_args(int ac, char **av, char **envp);

/*HERE_DOC*/
void	create_hd(t_pipex *p);
int		ft_str_search(const char *big_one, const char *lil_one);
char	*ft_duplicate(char *str, int n);
void	first_heredoc(t_pipex *p, char **envp);
void	here_or_not(int ac, char **av, t_pipex *p, char **envp);

/*GET_NEXT_LINE*/
char	*get_next_line(int fd);
char	*ft_buf(char *buf, int *x);
char	*ft_next(char *buf, int fd);
char	*ft_rest(int x, char *buf);

#endif
