/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbaumeis <lbaumeis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 16:45:55 by lbaumeis          #+#    #+#             */
/*   Updated: 2024/07/26 13:22:20 by lbaumeis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft/libft.h"
#include <fcntl.h>

char	**get_envp(void)
{
	char	*temp_env;
	char	**copy_env;

	temp_env = NULL;
	copy_env = NULL;
	temp_env = getenv("PATH");
	if (!temp_env)
	{
		perror("envp");
		exit(EXIT_FAILURE);
	}
	copy_env = ft_split(temp_env, ':');
	if (!copy_env)
	{
		free(temp_env);
		temp_env = NULL;
		perror("envp");
		exit(EXIT_FAILURE);
	}
	while (*copy_env)
	{
		printf("%s\n", *copy_env);
		copy_env++;
	}
}
