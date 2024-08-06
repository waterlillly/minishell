/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shittonofcmds.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbaumeis <lbaumeis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/03 14:33:31 by lbaumeis          #+#    #+#             */
/*   Updated: 2024/08/06 19:18:58 by lbaumeis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	shittonofcmds(t_pipex *p)
{
	int		cmds;
	int		x;
	int		circles;
	char	***avv;

	cmds = p->cmd_count;
	circles = 0;
	x = 0;
	circles = cmds / 512;
	if (cmds % 512 != 0)
		circles ++;
	avv = NULL;
	avv = malloc(sizeof(char **) * (circles + 1));
	if (!avv)
	{
		perror("malloc");
		err_free(p, 1);
	}
	while (x < circles)
	{
	
	}
}