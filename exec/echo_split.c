/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_split.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbaumeis <lbaumeis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/31 17:54:22 by lbaumeis          #+#    #+#             */
/*   Updated: 2024/10/13 14:28:33 by lbaumeis         ###   ########.fr       */
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
	while (s && s[i])
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
	while (s && s[i])
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

// void	xpd(t_pipex *p, t_minishell_p *pars)
// {
// 	int		i;
// 	int		j;
// 	char	**tmp;	

// 	if (!pars || !pars->str)
// 		return ;
// 	while (pars)
// 	{
// 		i = 0;
// 		tmp = NULL;
// 		pars->ps = NULL;
// 		pars->ps = ft_calloc(ft_arrlen(pars->str) + 1, sizeof(char *));
// 		if (!pars->ps)
// 			return ;
// 		while (pars->str[i])
// 		{
// 			tmp = d_q_space(xpd_dollar(xpd_space(xpd_single(xpd_double(xpd_start(pars, i))))));
// 			j = 0;
// 			while (tmp && tmp[j])
// 			{
// 				//printf("tmp[%d]: %s\n", j, tmp[j]);
// 				pars->ps[i] = ft_strjoin_free_both(pars->ps[i], xpand(p, tmp, j));
// 				free(tmp[j]);
// 				//printf("ps[%d]: %s\n", i, pars->ps[i]);
// 				j++;
// 			}
// 			free(tmp);
// 			i++;
// 		}
// 		pars = pars->next;
// 	}
// }

bool	is_quote(int q)
{
	if (q == '\'' || q == '\"')
		return (true);
	return (false);
}

int	xpd_count(char *s)
{
	int		q;
	int		i;
	int		c;

	i = 0;
	c = 0;
	if (!s)
		return (0);
	while (s[i])
	{
		if (s[i] && !is_quote(s[i]))
		{
			i++;
			while (s[i] && !is_quote(s[i]))
				i++;
		}
		else
		{
			q = s[i];
			i++;
			while (s[i] && s[i] != q)
				i++;
		}
		c++;
	}
	return (c);
}

char	**xpd_split(char *s)
{
	char	**ps;
	char	*temp;
	int		q;
	int		i;
	int		x;
	int		c;
	int		y;

	ps = NULL;
	y = 0;
	ps = ft_calloc(xpd_count(s) + 1, sizeof(char *));
	if (!ps)
		return (NULL);
	i = 0;
	if (!s)
		return (NULL);
	while (s[i])
	{
		temp = NULL;
		if (s[i] && !is_quote(s[i]))
		{
			x = i;
			c = 0;
			//i++;
			while (s[i] && !is_quote(s[i]))
			{
				c++;
				i++;
			}
			if (is_quote(s[i]))
				i++;
		}
		else
		{
			q = s[i];
			x = i;
			c = 1;
			i++;
			while (s[i] && s[i] != q)
			{
				c++;
				i++;
			}
			if (s[i] == q)
				i++;
			c++;
		}
		//i++;
		ps[y] = ft_substr(s, x, c);
		if (!ps[y])
			return (ft_free_double(ps), NULL);
		y++;
	}
	return (ps);
}

// char	**xpd_quotes(t_minishell_p *pars, int i)
// {
// 	char	**s;
// 	int		x;

// 	if (!pars || !pars->str)
// 		return (NULL);
// 	s = NULL;
// 	x = 0;
// 	while (pars->str[i][x] && pars->str[i][x] != '\'' && pars->str[i][x] != '\"')
// 		x++;
// 	if (pars->str[i][x])
// 		s = xpd_1_split(pars->str[i], pars->str[i][x]);
// 	else
// 	{
// 		s = ft_calloc(2, sizeof(char *));
// 		if (!s)
// 			return (NULL);
// 		s[0] = ft_strdup(pars->str[i]);
// 	}
// 	return (s);
// }

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
			tmp = d_q_space(xpd_dollar(xpd_slash(xpd_split(pars->str[i]))));//xpd_space(
			j = 0;
			while (tmp && tmp[j])
			{
				//printf("\ntmp[%d]: %s\n", j, tmp[j]);
				pars->ps[i] = ft_strjoin_free_both(pars->ps[i], xpand(p, tmp, j));
				free(tmp[j]);
				//printf("ps[%d]: %s\n\n", i, pars->ps[i]);
				j++;
			}
			free(tmp);
			i++;
		}
		pars = pars->next;
	}
}