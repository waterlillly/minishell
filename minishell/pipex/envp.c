/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbaumeis <lbaumeis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 15:48:38 by lbaumeis          #+#    #+#             */
/*   Updated: 2024/08/06 19:18:21 by lbaumeis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	get_envp(t_pipex *p)
{
	char	*temp_env;

	p->envp = NULL;
	temp_env = NULL;
	temp_env = getenv("PATH");
	if (!temp_env)
	{
		perror("envp");
		exit(EXIT_FAILURE);
	}
	p->envp = ft_split(temp_env, ':');
	if (!p->envp)
	{
		free(temp_env);
		temp_env = NULL;
		perror("envp");
		exit(EXIT_FAILURE);
	}
	while (*p->envp)
	{
		printf("%s\n", *p->envp);
		p->envp++;
	}
}
