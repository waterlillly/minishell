/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbaumeis <lbaumeis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 14:55:29 by lbaumeis          #+#    #+#             */
/*   Updated: 2024/07/18 20:24:52 by lbaumeis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	create_hd(t_pipex *p)
{
	p->hd = open("hd", O_CREAT, O_RDWR, 0644);
	if (p->hd == -1)
	{
		perror("open");
		err_free(p, 1);
	}
}

int	ft_str_search(const char *big_one, const char *lil_one)
{
	char	*big;
	char	*lil;
	int		x;
	int		y;

	big = (char *)big_one;
	lil = (char *)lil_one;
	x = 0;
	while (big[x])
	{
		y = 0;
		if (big[x] && big[x] == lil[0])
		{
			y = 0;
			while (big[x] && lil[y] && big[x] == lil[y])
			{
				x++;
				y++;
			}
			if (lil[y] == '\0')
				return (x - y - 1);
		}
		x++;
	}
	return (-1);
}

char	*ft_duplicate(char *str, int n)
{
	int		x;
	char	*s;
	char	*new;

	x = 0;
	s = (char *)str;
	new = malloc(sizeof(char) * (n + 1));
	if (!new)
		return (NULL);
	while (s[x] && x <= n)
	{
		new[x] = s[x];
		x++;
	}
	new[x] = '\0';
	free(str);
	str = NULL;
	return (new);
}

void	first_heredoc(t_pipex *p, char **envp)
{
	char	*line;
	char	*last;
	int		x;
	
	line = NULL;
	last = NULL;
	create_hd(p);
	x = ft_str_search(line, p->delimiter);
	while (x < 0)
	{
		ft_putstr_fd(line, p->hd);
		free(line);
		line = get_next_line(STDIN_FILENO);
		x = ft_str_search(line, p->delimiter);
	}
	last = ft_duplicate(line, x);
	ft_putstr_fd(last, p->hd);
	free(last);
	last = NULL;
	p->filein = p->hd;
	close(p->hd);
	first(p, envp);
}

void	here_or_not(int ac, char **av, t_pipex *p, char **envp)
{
	if (!ft_strcmp(av[1], "here_doc"))
	{
		p->x = 2;
		p->cmd_count = ac - 3;
		check_filein(p);
		p->delimiter = NULL;
	}
	else
	{
		p->x = 3;
		p->delimiter = av[2];
		p->cmd_count = ac - 4;
		first_heredoc(p, envp);
	}
}
