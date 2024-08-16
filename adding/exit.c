/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbaumeis <lbaumeis@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 16:21:59 by lbaumeis          #+#    #+#             */
/*   Updated: 2024/08/14 15:43:34 by lbaumeis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exit_shell(t_pipex *p, char *str, int exit_code)
{
	err_free(p);
	perror(str);
	exit(exit_code);
}

int	error(char *str, int code)
{
	perror(str);
	exit(code);
}
