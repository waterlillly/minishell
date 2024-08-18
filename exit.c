/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbaumeis <lbaumeis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 16:21:59 by lbaumeis          #+#    #+#             */
/*   Updated: 2024/08/17 16:53:25 by lbaumeis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exit_shell(t_pipex *p, t_minishell_p *pars, t_raw_in *input, char *str)
{
	int	x;

	x = p->status;
	free_everything(p, pars, input);
	perror(str);
	exit(x);
}

int	error(char *str, int code)
{
	perror(str);
	return (code);
}

void	free_everything(t_pipex *p, t_minishell_p *pars, t_raw_in *input)
{
	if (p)
		err_free(p);
	if (pars)
		free_parse(pars);
	if (input)
		free_raw(input);
}
