/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbaumeis <lbaumeis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 16:50:42 by lbaumeis          #+#    #+#             */
/*   Updated: 2024/09/11 16:24:18 by lbaumeis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	count_out_files(t_minishell_p *pars)
{
	t_minishell_p	*tmp;
	int				x;

	tmp = pars;
	x = 0;
	while (tmp && tmp->redirect && tmp->redirect->input && tmp->redirect->token
		&& (tmp->redirect->token == BIGGER
		|| tmp->redirect->token == BIGGERBIGGER))
	{
		tmp->redirect = tmp->redirect->next;
		x++;
	}
	return (x);
}

int	count_in_files(t_minishell_p *pars)
{
	t_minishell_p	*tmp;
	int				x;

	tmp = pars;
	x = 0;
	while (tmp && tmp->redirect && tmp->redirect->input
		&& tmp->redirect->token && tmp->redirect->token == SMALLER)
	{
		x++;
		tmp->redirect = tmp->redirect->next;
	}
	return (x);
}

void	check_filein(t_pipex *p, t_minishell_p *pars)
{
	int				*arr;
	t_minishell_p	*tmp;
	int				num_files;
	int				x;

	tmp = pars;
	num_files = count_in_files(pars);
	//printf("infile counter: %d\n", num_files);
	x = 0;
	arr = malloc(sizeof(int) * num_files);
	if (!arr)
		return (perror("malloc"));
	while (tmp && tmp->redirect && tmp->redirect->input
		&& tmp->redirect->token == SMALLER)
	{
		arr[x] = open(tmp->redirect->input, O_RDONLY, 0644);
		if (arr[x] == -1 || access(tmp->redirect->input, R_OK) == -1)
			return (perror(tmp->redirect->input));
		p->filein = arr[x];
		ft_putnbr_fd(p->filein, 1);
		x++;
		tmp->redirect = tmp->redirect->next;
	}
	//arr[x] = '\0';
	// if (arr)
	// 	return (arr);
	// return (NULL);
}

void	check_fileout(t_pipex *p, t_minishell_p *pars)
{
	int				f;
	//t_minishell_p	*tmp;
	int				num_files;
	//int				x;

	f = -1;
	//tmp = pars;
	num_files = count_out_files(pars);
	printf("outfile counter: %d\n", num_files);
	//x = 0;
	if (p && pars && pars->redirect)
	{
		puts("B\n");
		while (pars->redirect && pars->redirect->input)
			// && (pars->redirect->token == BIGGER
			// || pars->redirect->token == BIGGERBIGGER))
		{
			printf("fileout: %s\n", pars->redirect->input);
			if (pars->redirect->token == BIGGER)
			{
				f = open(pars->redirect->input, O_WRONLY | O_CREAT | O_TRUNC, 0644);
				if (f == -1 || access(pars->redirect->input, W_OK) == -1)
					return (perror("file"));
			}
			else if (pars->redirect->token == BIGGERBIGGER)
			{
				f = open(pars->redirect->input, O_RDWR | O_CREAT | O_APPEND, 0644);
				if (f == -1 || access(pars->redirect->input, W_OK) == -1)
					return (perror("file"));
			}
			if (f != -1)
			{
				puts("A\n");
				p->fileout = f;
				ft_putnbr_fd(p->fileout, 1);
				//x++;
			}
			pars->redirect = pars->redirect->next;
		}
	}
	// arr[x] = '\0';
	// if (arr)
	// 	return (arr);
	// return (NULL);
}
