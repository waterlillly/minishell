/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbaumeis <lbaumeis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 16:21:59 by lbaumeis          #+#    #+#             */
/*   Updated: 2024/10/14 18:08:03 by lbaumeis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exit_shell(t_pipex *p, t_minishell_p *pars, t_raw_in *input, char *str)
{
	close_all(p);
	if (p->pip)
	{
		free(p->pip);
		p->pip = 0;
	}
	if (p->paths)
		ft_free_2d(p->paths);//ft_free_2d(p->paths);
	if (p->xport)
		ft_free_2d(p->xport);//ft_free_double(p->xport);
	if (p->menv)
		ft_free_2d(p->menv);
	free_p_rest(p);
	free_everything(p, pars, input);
	if (str)
		perror(str);
}

int	error(char *str, int code)
{
	perror(str);
	return (code);
}

static char	*trim_exit(char *s)
{
	char	*tmp;
	int		x;
	bool	flag;
	
	tmp = NULL;
	if (s)
	{
		x = 0;
		flag = false;
		if (x == 0 && (s[x] == '-' || s[x] == '+'))
		{
			x++;
			flag = true;
		}
		while (s[x] && s[x] == '0')
			x++;
		tmp = ft_substr(s, x, ft_strlen(s) - x);
		if (flag == true)
			tmp = ft_strjoin_free_both(ft_strdup("-"), tmp);
		return (tmp);
	}
	return (NULL);
}

char	*check_exit(t_pipex *p, t_minishell_p *pars)
{
	char	*str;
	char	*tmp;

	str = NULL;
	tmp = NULL;
	if (pars->ps && !ft_strcmp_bool(pars->ps[0], "exit"))
		return (p->exit = false, NULL);
	if (pars->ps && ft_strcmp_bool(pars->ps[0], "exit"))
	{
		p->exit_count++;
		if (!pars->ps[1] && !pars->next)
			return (p->exit = true, NULL);
		else if (pars->ps[1] && !pars->ps[2] && (ft_isdigit(pars->ps[1][0])
			|| ((pars->ps[1][0] == '+' || pars->ps[1][0] == '-')
			&& pars->ps[1][1] != '-' && pars->ps[1][1] != '+')))
		{
			tmp = trim_exit(pars->ps[1]);
			p->status = ft_atoi_long(tmp);
			free(tmp);
			if (!pars->next && p->exit_count == 1)
				return (p->exit = true, NULL);
			else
				return (p->exit = false, NULL);
		}
		else if (pars->ps[1] && (ft_isalpha(pars->ps[1][0]) || pars->ps[1][0] == '-'
			|| pars->ps[1][0] == '+' || ft_strlen(pars->ps[1]) == 0))
		{
			if (ft_strlen(pars->ps[1]) == 0)
				str = ft_strdup("exit: numeric argument required");
			else
				str = ft_strjoin("exit: ", ft_strjoin(pars->ps[1], ": numeric argument required"));
			p->status = 2;
			if (!pars->next && p->exit_count == 1)
				return (p->exit = true, str);
			return (p->exit = false, str);
		}
		else if (pars->ps[1] && pars->ps[2])
		{
			str = ft_strdup("exit: too many arguments");
			p->status = 1;
			return (p->exit = false, str);
		}
		else
			return (p->exit = false, NULL);
	}
	return (p->exit = false, NULL);
}
