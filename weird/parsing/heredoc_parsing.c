/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_parsing.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbaumeis <lbaumeis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 13:02:16 by lbaumeis          #+#    #+#             */
/*   Updated: 2024/07/23 13:15:49 by lbaumeis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <fcntl.h>
#include <error.h>
#include <stdio.h>
#include <stdlib.h>

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
