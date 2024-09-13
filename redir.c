/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbaumeis <lbaumeis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 16:50:42 by lbaumeis          #+#    #+#             */
/*   Updated: 2024/09/13 14:34:57 by lbaumeis         ###   ########.fr       */
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
}

void	check_fileout(t_pipex *p, t_minishell_p *pars)
{
	int				f;
	int				num_files;

	f = -1;
	num_files = count_out_files(pars);
	if (p && pars && pars->redirect)
	{
		while (pars->redirect && pars->redirect->input)
		{
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
				p->fileout = f;
				ft_putnbr_fd(p->fileout, 1);
			}
			pars->redirect = pars->redirect->next;
		}
	}
}
