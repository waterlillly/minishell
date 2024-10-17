/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_split.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbaumeis <lbaumeis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/31 17:54:22 by lbaumeis          #+#    #+#             */
/*   Updated: 2024/10/17 20:25:25 by lbaumeis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	**rewrite(char **s, int c)
{
	int		i;
	int		j;
	char	**arr;

	(i = 0, j = 0);
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
				(arr[j] = ft_strjoin_free_one(arr[j], s[i]), i++);
			if (s[i] && count_q(s[i], '\'') % 2 != 0)
				(arr[j] = ft_strjoin_free_one(arr[j], s[i]), i++);
		}
		else if (s[i] && count_q(s[i], '\"') % 2 != 0 && s[i][0] == '\"')
		{
			i++;
			while (s[i] && count_q(s[i], '\"') % 2 == 0)
				(arr[j] = ft_strjoin_free_one(arr[j], s[i]), i++);
			if (s[i] && count_q(s[i], '\"') % 2 != 0)
				(arr[j] = ft_strjoin_free_one(arr[j], s[i]), i++);
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

	(i = 0, c = ft_arrlen(s));
	while (s && s[i])
	{
		if (s[i] && count_q(s[i], '\'') % 2 != 0 && s[i][0] == '\'')
		{
			i++;
			while (s[i] && count_q(s[i], '\'') % 2 == 0)
				(c--, i++);
			if (s[i] && count_q(s[i], '\'') % 2 != 0)
				(c--, i++);
		}
		else if (s[i] && count_q(s[i], '\"') % 2 != 0 && s[i][0] == '\"')
		{
			i++;
			while (s[i] && count_q(s[i], '\"') % 2 == 0)
				(c--, i++);
			if (s[i] && count_q(s[i], '\"') % 2 != 0)
				(c--, i++);
		}
		else
			i++;
	}
	return (rewrite(s, c));
}

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

	(i = 0, c = 0);
	if (!s)
		return (0);
	while (s[i])
	{
		if (s[i] && !is_quote(s[i]))
		{
			while (s[i] && !is_quote(s[i]))
				i++;
		}
		else
		{
			(q = s[i], i++);
			while (s[i] && s[i] != q)
				i++;
			i++;
		}
		c++;
	}
	return (c);
}

char	**xpd_split(char *s)
{
	char	**ps;
	int		q;
	int		i;
	int		x;
	int		c;
	int		y;

	(ps = NULL, y = 0);
	if (!s)
		return (NULL);
	ps = ft_calloc(xpd_count(s) + 1, sizeof(char *));
	if (!ps)
		return (NULL);
	i = 0;
	while (s[i])
	{
		if (s[i] && !is_quote(s[i]))
		{
			(x = i, c = 0);
			while (s[i] && !is_quote(s[i]))
				(c++, i++);
		}
		else
		{
			(q = s[i], x = i, c = 1, i++);
			while (s[i] && s[i] != q)
				(c++, i++);
			if (s[i] == q)
				i++;
			c++;
		}
		ps[y] = ft_substr(s, x, c);
		if (!ps[y])
			return (ft_free_2d(ps), NULL);
		y++;
	}
	return (ps);
}


bool	only_space_dollar(char *s)
{
	size_t	i;

	i = 0;
	if (s && d_out_q(s))
	{
		while (s[i])
		{
			if (i == 0 && s[i] == '\"')
				i++;
			else if (i == ft_strlen(s) - 1 && ft_strlen(s) > 2 && s[i] == '\"')
				return (true);
			else if (s[i] == ' ')
				i++;
			else if (s[i] == '$')
				i++;
			else
				return (false);				
		}
	}
	return (false);
}

// char	**xpd_s_in_d(char **s)
// {
// 	int		i;
// 	int		j;
// 	int		x;
// 	char	**t;
// 	char	*ts;

// 	i = 0;
// 	while (s[i])
// 	{
// 		if (d_out_q(s[i]))
// 		{
// 			j = 0;
// 			t = NULL;
// 			ts = NULL;
// 			t = xpd_3_split(rm_out_q(s[i]), ' ');
// 			while (t[j])
// 			{
// 				if (s_out_q(t[j]) && ft_strchr(t[j], '$'))
// 				{
// 					while (*t[j] && *t[j] != '$')
// 						t[j]++;
// 					if (*t[j])
// 					{
// 						x = *t[j];
// 						while (*t[j] && *t[j] != ' ')
// 							t[j]++;
// 						if (*t[j])
// 							ts = ft_substr(t[j], x + 1, *t[j] - x);
// 					}
// 					if (ts)
// 				}
// 			}
// 		}
// 	}
// }

void	xpd(t_pipex *p, t_minishell_p *pars)
{
	int		i;
	int		j;
	char	**tmp;
	char	*xpd;
	
	if (!pars || !pars->str)
		return ;
	while (pars)
	{
		(i = 0, tmp = NULL, pars->ps = NULL);
		pars->ps = ft_calloc(ft_arrlen(pars->str) + 1, sizeof(char *));
		if (!pars->ps)
			return ;
		while (pars->str[i])
		{
			if (only_space_dollar(pars->str[i]))
				pars->ps[i] = rm_out_q(pars->str[i]);
			else
			{
				tmp = xpd_split(pars->str[i]);
				//(puts("\n***1***"), ft_print_array(tmp), puts("*******\n"));
				// tmp = xpd_s_in_d(tmp);
				// (puts("\n***2***"), ft_print_array(tmp), puts("*******\n"));
				tmp = d_q_space(tmp);
				//(puts("\n***3***"), ft_print_array(tmp), puts("*******\n"));
				tmp = xpd_dollar(tmp);
				//(puts("\n***4***"), ft_print_array(tmp), puts("*******\n"));
				tmp = xpd_slash(tmp);
				//(puts("\n***5***"), ft_print_array(tmp), puts("*******\n"));
				tmp = xpd_ec(tmp, p);
				//(puts("\n***6***"), ft_print_array(tmp), puts("*******\n"));
				j = 0;
				while (tmp && tmp[j])
				{
					//printf("\ntmp[%d]: %s\n", j, tmp[j]);
					xpd = NULL;
					if (i > 0 && pars->ps[i - 1] && (ft_strcmp_bool(pars->ps[i - 1], "echo")
						|| ft_strcmp_bool(pars->ps[i - 1], "/bin/echo")))
						xpd = xpand(p, tmp, j, 1);
					else
						xpd = xpand(p, tmp, j, 0);
					pars->ps[i] = ft_strjoin_free_both(pars->ps[i], xpd);
					free(tmp[j]);
					//printf("ps[%d]: %s\n\n", i, pars->ps[i]);
					j++;
				}
				free(tmp);
			}
			i++;
		}
		pars = pars->next;
	}
}
