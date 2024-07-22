/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbaumeis <lbaumeis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 14:55:29 by lbaumeis          #+#    #+#             */
/*   Updated: 2024/07/22 18:42:29 by lbaumeis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

// signal_reset
// {
// 	if (g_sig = SIGINT)
// 		errno_code = 130;
// 	if (g_sig = SIgQUIT)
// 		errno_code = 131;
// 	g_sig = 0;	
// }

// int heredoc(t_pipex *p)
// {
// 	if (g_sig != 0)
// 	{
// 		reset_signal(mini, g_sig)
// 	}
// 	while (1)
// 	{
// 		if (first_heredoc(p) == 1)
// 			break;
// 	}
// }

/*
int	read_heredoc(char *lim)
{
	char	*line;
	int		hd;
	
	line = NULL;
	hd = -1;
	hd = open("hd", O_CREAT, O_RDWR, O_APPEND, 0777);
	if (hd == -1)
	{
		perror("hd");
		exit(EXIT_FAILURE);
	}
	line = readline("> ");
	while (line && !ft_strcmp(line, lim))
	{
		ft_putstr_fd(line, hd);
		free(line);
		line = NULL;
		line = readline("> ");
	}
	close(hd);
	return (hd);
}

int	heredoc(int ac, char **av)
{
	int		x;
	int		hd;
	char	*lim;

	x = 1;//dont check av[0] 
	hd = -1;
	lim = NULL;
	while (av[x] && x < ac)
	{
		if (ft_strcmp(av[x], "here_doc"))
		{
			lim = av[x + 1];
			hd = read_heredoc(lim);
			return (hd);
		}
		x++;
	}
	return (-1);
}
*/
void	first_heredoc(t_pipex *p)
{
	char	*line;
	
	line = NULL;
	check_filein(p);
	line = readline("> ");
	while (line && !ft_strcmp(line, p->delimiter))
	{
		ft_putstr_fd(line, p->filein);
		free(line);
		line = NULL;
		line = readline("> ");
	}
	free(line);
	line = NULL;
}

void	here_or_not(t_pipex *p)
{
	if (!ft_strcmp(p->av[1], "here_doc"))
	{
		p->x = 2;
		p->cmd_count = p->ac - 3;
		p->delimiter = NULL;
		if (p->in == true)
			check_filein(p);
	}
	else
	{
		p->x = 3;
		p->delimiter = p->av[2];
		p->cmd_count = p->ac - 4;
		first_heredoc(p);
	}
}
