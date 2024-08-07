/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbaumeis <lbaumeis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 16:21:59 by lbaumeis          #+#    #+#             */
/*   Updated: 2024/08/07 22:10:20 by lbaumeis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

void	error(t_pipex *p, char *str, int exit_code)//add struct minishell+buildins+pipex
{
	perror(str);
	err_free(p);
	exit(exit_code);
}
