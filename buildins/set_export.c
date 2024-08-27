/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_export.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbaumeis <lbaumeis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/03 11:59:53 by lbaumeis          #+#    #+#             */
/*   Updated: 2024/08/27 16:46:50 by lbaumeis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	update_export(t_pipex *p, char *tok, char *token)
{
	int		x;
	char	*temp;
	char	*temp1;

	x = 0;
	temp = NULL;
	temp1 = NULL;
	temp = ft_strjoin("declare -x ", tok);
	if (!temp)
		return (1);
	x = find_str_part(p->xport, temp);
	if (x == -1)
		return (free(temp), temp = NULL, 1);
	temp1 = ft_strjoin_free_both(ft_strdup("="),
		add_quotes(ft_substr(token, ft_strlen(tok) + 1,
		ft_strlen(token) - ft_strlen(tok))));
	if (!temp1)
		return (free(temp), temp = NULL, 1);
	p->xport[x] = ft_strjoin_free_both(temp, temp1);
	if (!p->xport[x])
		return (1);
	return (0);
}

int	set_export(t_pipex *p, char **token)
{
	char	*temp;
	int		x;

	x = 0;
	if (!p || !token || !ft_strcmp_bool(token[0], "export") || !token[1])
		return (1);
	if (token[1][0] == '$')
		return (perror("not a valid identifier"), 1);
	temp = strcpy_until(token[1]);
	if (!temp)
		return (1);
	if (valid_env(p, temp))
	{
		if (ft_strchr(remove_quotes(token[1]), '='))
		{
			if (find_str_part(p->menv, temp) < 0)
				return (free(temp), temp = NULL, 1);
			p->menv[find_str_part(p->menv, temp)] = remove_quotes(token[1]);
			if (!p->menv[x])
				return (free(temp), temp = NULL, x);
		}
		x = update_export(p, temp, remove_quotes(token[1]));
	}
	else
		x = add_to_export(p, remove_quotes(token[1]));
	return (free(temp), temp = NULL, x);
}

int	update(t_pipex *p, char *set, char *tok)
{
	char	*temp;
	int		x;

	temp = NULL;
	x = 0;
	if (!p || !set || !tok)
		return (0);
	if (!is_access(tok))
		return (perror(tok), 1);
	x = find_str_part(p->menv, set);
	if (x < 0)
		return (1);
	temp = ft_strjoin(set, "=");
	if (!temp)
		return (1);
	p->menv[x] = ft_strjoin_free_one(temp, tok);
	if (!p->menv[x])
		return (1);
	return (update_export(p, set, tok));
}

int	update_both(t_pipex *p)
{
	int		x;

	x = 0;
	x = update(p, "OLDPWD", get_env(p, "PWD"));
	if (x != 0)
		return (x);
	x = update(p, "PWD", getcwd(NULL, 0));
	return (x);
}
