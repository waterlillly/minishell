/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbaumeis <lbaumeis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 16:21:59 by lbaumeis          #+#    #+#             */
/*   Updated: 2024/08/10 19:59:47 by lbaumeis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

void	error(t_pipex *p, char *str, int exit_code)//add struct minishell+buildins+pipex
{
	err_free(p);
	perror(str);
	exit(exit_code);
}
