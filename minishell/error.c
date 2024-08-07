/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbaumeis <lbaumeis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 17:49:59 by codespace         #+#    #+#             */
/*   Updated: 2024/08/07 16:13:56 by lbaumeis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int error(t_raw_in *in, char *str, int code)
{
	//if (ms->e)
	//	err_free(ms);
	if (in)
		free_raw(in);
	//ft_bzero(ms, sizeof(t_ms));
	perror(str);
	//ft_putendl_fd(str, 2);
	exit(code);
	return (code);
}