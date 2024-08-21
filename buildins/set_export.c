/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_export.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgardesh <mgardesh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/03 11:59:53 by lbaumeis          #+#    #+#             */
/*   Updated: 2024/08/21 17:49:06 by mgardesh         ###   ########.fr       */
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
	if (!p || !tok || !token)
		return (1);
	temp = ft_strjoin("declare -x ", tok);
	if (!temp)
		return (1);//error(p, "strjoin", p->status);
	//free(tok);
	//tok = NULL;
	x = find_str_part(p->xport, temp);
	if (x == -1)
		return (free(temp), temp = NULL, 1);//error(p, "couldnt find argument", p->status);
	temp1 = add_quotes(token);
	if (!temp1)
		return (free(temp), temp = NULL, 1);//error(p, "modify_quotes", p->status);
	free(p->xport[x]);
	//p->xport[x] = NULL;
	p->xport[x] = ft_strjoin_free_both(temp, temp1);
	if (!p->xport[x])
		return (1);//error(p, "strjoin_free_both", p->status);
	return (0);
}

int	set_export(t_pipex *p, char **token)
{
	char	*temp;
	int		x;

	temp = NULL;
	x = 0;
	if (!p || !token || !ft_strcmp_bool(token[0], "export") || !token[1])
		return (1);
	if (token[1][0] == '$')
		return (perror("not a valid identifier"), 1);
	temp = strcpy_until(token[1]);
	if (!temp)
		return (1);//error(p, "copy_until", p->status);
	if (valid_env(p, temp))
	{
		if (ft_strchr(remove_quotes(token[1]), '='))
			p->menv[find_str_part(p->menv, temp)] = remove_quotes(token[1]);
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
	if (!p || !p->menv || !p->xport || !tok)
		return (0);
	if (!is_access(tok))
		return (perror("is_access(tok)"), 1);
	x = find_str_part(p->menv, set);
	if (x < 0)
		return (1);
	temp = ft_strjoin(set, "=");
	if (!temp)
		return (1);
	p->menv[x] = NULL;
	p->menv[x] = ft_strjoin_free_one(temp, tok);
	if (!p->menv[x])
		return (1);
	return (update_export(p, set, tok));
}

int	update_both(t_pipex *p)
{
	int	x;

	x = 0;
	x = update(p, "PWD", p->pwd);
	if (x != 0)
		return (x);
	x = update(p, "OLDPWD", p->oldpwd);
	return (x);
}
