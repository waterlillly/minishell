/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbaumeis <lbaumeis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 16:50:42 by lbaumeis          #+#    #+#             */
/*   Updated: 2024/09/09 17:04:43 by lbaumeis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


//redir infiles
// int	*arr;
// 	int	x;

// 	if (!p || !pars)
// 		return (1);
// 	x = 0;
// 	if (pars->redirect->token == SMALLER)
// 	{
// 		arr = check_filein(p, pars);
// 		while (arr && arr[x])
// 		{
// 			printf("infile %d\n", x);
// 			if (arr[x] != 1)
// 			{
// 				if (dup2(arr[x], STDIN_FILENO) == -1)
// 					return (perror("dup2 filein"), 1);
// 				close(arr[x]);
// 				x++;
// 			}
// 		}
// 	}

//redir outfiles
// x = 0;
// 	if (pars->redirect->token == BIGGER
// 		|| pars->redirect->token == BIGGERBIGGER)
// 	{
// 		arr = check_fileout(p, pars);
// 		while (arr && arr[x])
// 		{
// 			printf("outfile %d\n", x);
// 			if (arr[x] != -1)
// 			{
// 				if (dup2(arr[x], STDOUT_FILENO) == -1)
// 					return (perror("dup2 fileout"), 1);
// 				close(arr[x]);
// 			}
// 			x++;
// 		}
// 	}

// int	redirect_in(t_pipex *p, int c, t_minishell_p *pars)
// {
// 	int	*arr;
// 	int	x;

// 	if (!p || !pars)
// 		return (1);
// 	x = 0;
// 	if (pars->redirect->token == SMALLER)
// 	{
// 		arr = check_filein(p, pars);
// 		while (arr && arr[x])
// 		{
// 			printf("infile %d\n", x);
// 			if (arr[x] != 1)
// 			{
// 				if (dup2(arr[x], STDIN_FILENO) == -1)
// 					return (perror("dup2 filein"), 1);
// 				x++;
// 			}
// 		}
// 	}
// 	else if (p && p->pip[c]  && p->cmd_count > 1 && c == 0)//
// 	{
// 		if (p->pip[c][1] != -1 && p->pip[c][1] != STDOUT_FILENO)
// 			close(p->pip[c][1]);
// 		printf("c - out: %d\n", c);
// 		if (dup2(p->pip[c][0], STDIN_FILENO) == -1)
// 			return (perror("dup2 c=0 redir input"), 1);
// 	}
// 	else if (p && p->pip[c - 1] && p->cmd_count > 1 && c > 0 && c < p->cmd_count - 1)//
// 	{
// 		if (p->pip[c - 1][1] != -1 && p->pip[c - 1][1] != STDOUT_FILENO)//ls| wc stays open without it
// 		 	close(p->pip[c - 1][1]);
// 		printf("c - out: %d\n", c);
// 		if (dup2(p->pip[c - 1][0], STDIN_FILENO) == -1)
// 			return (perror("dup2 c - 1 redir input"), 1);
// 	}
// 	// else if (c == p->cmd_count - 1)
// 	// {
// 	// 	if (dup2(STDIN_FILENO, p->copy_stdin) == -1)
// 	// 		return (perror("dup2 p->copy_stdin"), 1);
// 	// 	close(p->copy_stdin);
// 	// }
// 	closing(p);
// 	return (0);
// }

// int	redirect_out(t_pipex *p, int c, t_minishell_p *pars)
// {
// 	int	*arr;
// 	int	x;

// 	if (!p || !pars)
// 		return (1);
// 	x = 0;
// 	if (pars->redirect->token == BIGGER
// 		|| pars->redirect->token == BIGGERBIGGER)
// 	{
// 		arr = check_fileout(p, pars);
// 		while (arr && arr[x])
// 		{
// 			printf("outfile %d\n", x);
// 			if (arr[x] != -1)
// 			{
// 				if (dup2(arr[x], STDOUT_FILENO) == -1)
// 					return (perror("dup2 fileout"), 1);
// 			}
// 			x++;
// 		}
// 	}
// 	else if (p && p->pip[c] && p->cmd_count > 1 && c < p->cmd_count - 1)//
// 	{
// 		if (c != 0 && p->pip[c][0] != -1 && p->pip[c][0] != STDIN_FILENO)
// 			close(p->pip[c][0]);
// 		printf("c - in: %d\n", c);
// 		if (dup2(p->pip[c][1], STDOUT_FILENO) == -1)
// 			return (perror("dup2 redir output"), 1);
// 	}
// 	// else if (c == p->cmd_count - 1)
// 	// {
// 	// 	if (dup2(STDOUT_FILENO, p->copy_stdout) == -1)
// 	// 		return (perror("dup2 p->copy_stdout"), 1);
// 	// 	close(p->copy_stdout);
// 	// }
// 	closing(p);
// 	return (0);
// }
/*
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

int	*check_filein(t_pipex *p, t_minishell_p *pars)
{
	int				*arr;
	t_minishell_p	*tmp;
	int				num_files;
	int				x;

	tmp = pars;
	num_files = count_in_files(pars);
	x = 0;
	arr = malloc(sizeof(int) * num_files + 1);
	if (!arr)
		return (perror("malloc"), NULL);
	while (tmp && tmp->redirect && tmp->redirect->input
		&& tmp->redirect->token == SMALLER)
	{
		p->filein = open(tmp->redirect->input, O_RDONLY, 0644);
		if (p->filein == -1 || access(tmp->redirect->input, R_OK) == -1)
			return (perror(tmp->redirect->input), NULL);
		arr[x] = p->filein;
		ft_putnbr_fd(arr[x], 1);
		x++;
		tmp->redirect = tmp->redirect->next;
	}
	arr[x] = '\0';
	if (arr)
		return (arr);
	return (NULL);
}

int	*check_fileout(t_pipex *p, t_minishell_p *pars)
{
	int				*arr;
	t_minishell_p	*tmp;
	int				num_files;
	int				x;

	tmp = pars;
	num_files = count_out_files(pars);
	x = 0;
	arr = malloc(sizeof(int) * num_files + 1);
	if (!arr)
		return (perror("malloc"), NULL);
	while (tmp && tmp->redirect && tmp->redirect->input
		&& (tmp->redirect->token == BIGGER
		|| tmp->redirect->token == BIGGERBIGGER))
	{
		if (tmp->redirect->token == BIGGER)
		{
			p->fileout = open(tmp->redirect->input, O_WRONLY | O_CREAT | O_TRUNC, 0644);
			if (p->fileout == -1 || access(tmp->redirect->input, W_OK) == -1)
				return (perror("file"), NULL);
		}
		else if (tmp->redirect->token == BIGGERBIGGER)
		{
			p->fileout = open(tmp->redirect->input, O_RDWR | O_CREAT | O_APPEND, 0644);
			if (p->fileout == -1 || access(tmp->redirect->input, W_OK) == -1)
				return (perror("file"), NULL);
		}
		arr[x] = p->fileout;
		ft_putnbr_fd(arr[x], 1);
		x++;
		tmp->redirect = tmp->redirect->next;
	}
	arr[x] = '\0';
	if (arr)
		return (arr);
	return (NULL);
}
*/