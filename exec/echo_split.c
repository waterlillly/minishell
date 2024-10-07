/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_split.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbaumeis <lbaumeis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/31 17:54:22 by lbaumeis          #+#    #+#             */
/*   Updated: 2024/10/06 19:07:42 by lbaumeis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	**rewrite(char **s, int c)
{
	int		i;
	int		j;
	char	**arr;

	i = 0;
	j = 0;
	arr = ft_calloc(c + 1, sizeof(char *));
	if (!arr)
		return (NULL);
	while (s[i])
	{
		arr[j] = ft_strdup(s[i]);
		if (s[i] && count_q(s[i], '\'') % 2 != 0 && s[i][0] == '\'')
		{
			i++;
			while (s[i] && count_q(s[i], '\'') % 2 == 0)
			{
				arr[j] = ft_strjoin_free_one(arr[j], s[i]);
				i++;
			}
			if (s[i] && count_q(s[i], '\'') % 2 != 0)
			{
				arr[j] = ft_strjoin_free_one(arr[j], s[i]);
				i++;
			}
		}
		else if (s[i] && count_q(s[i], '\"') % 2 != 0 && s[i][0] == '\"')
		{
			i++;
			while (s[i] && count_q(s[i], '\"') % 2 == 0)
			{
				arr[j] = ft_strjoin_free_one(arr[j], s[i]);
				i++;
			}
			if (s[i] && count_q(s[i], '\"') % 2 != 0)
			{
				arr[j] = ft_strjoin_free_one(arr[j], s[i]);
				i++;
			}
		}
		else
			i++;
		j++;
	}
	return (ft_free_2d(s), arr);
}

char	**reformat(char **s)
{
	int	i;
	int	c;

	i = 0;
	c = ft_arrlen(s);
	while (s[i])
	{
		if (s[i] && count_q(s[i], '\'') % 2 != 0 && s[i][0] == '\'')
		{
			i++;
			//c--;
			while (s[i] && count_q(s[i], '\'') % 2 == 0)
			{
				c--;
				i++;
			}
			if (s[i] && count_q(s[i], '\'') % 2 != 0)
			{
				c--;
				i++;
			}
		}
		else if (s[i] && count_q(s[i], '\"') % 2 != 0 && s[i][0] == '\"')
		{
			i++;
			//c--;
			while (s[i] && count_q(s[i], '\"') % 2 == 0)
			{
				c--;
				i++;
			}
			if (s[i] && count_q(s[i], '\"') % 2 != 0)
			{
				c--;
				i++;
			}
		}
		else
			i++;
	}
	return (rewrite(s, c));
}

void	xpd(t_pipex *p, t_minishell_p *pars)
{
	int		i;
	int		j;
	char	**tmp;	

	if (!pars || !pars->str)
		return ;
	while (pars)
	{
		i = 0;
		tmp = NULL;
		pars->ps = NULL;
		pars->ps = ft_calloc(ft_arrlen(pars->str) + 1, sizeof(char *));
		if (!pars->ps)
			return ;
		while (pars->str[i])
		{
			tmp = d_q_space(xpd_dollar(xpd_space(xpd_single(xpd_double(xpd_start(pars, i))))));
			j = 0;
			while (tmp[j])
			{
				//printf("tmp[%d]: %s\n", j, tmp[j]);
				pars->ps[i] = ft_strjoin_free_one(pars->ps[i], xpand(p, tmp, j));
				//printf("ps[%d]: %s\n", i, pars->ps[i]);
				j++;
			}
			free(tmp);
			i++;
		}
		pars = pars->next;
	}
}
