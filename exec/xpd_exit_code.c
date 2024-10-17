/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xpd_exit_code.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbaumeis <lbaumeis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 17:41:16 by lbaumeis          #+#    #+#             */
/*   Updated: 2024/10/17 18:35:12 by lbaumeis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	count_ec_strs(char *s)
{
	int	counter;
	int	x;

	counter = 0;
	x = 0;
	while (s[x])
	{
		if (s[x] && s[x] == '$')
		{
			x++;
			if (s[x]&& s[x] == '?')
			{
				if (s[x])
					x++;
				counter++;
			}
		}
		else
		{
			while (s[x] && s[x] != '$')
				x++;
			counter++;
		}
	}
	return (counter);
}

static int	ec_split(char *s, int pa)
{
	if (s[pa] && s[pa] == '$' && s[pa + 1] && s[pa + 1] == '?')
		pa += 2;
	else
	{
		while (s[pa] && s[pa] != '$')
			pa++;
	}
	return (pa);
}

char	**xpd_ec_split(char *str)
{
	int		pa;
	int		pb;
	int		x;
	int		y;
	char	**s;

	x = 0;
	pa = 0;
	pb = 0;
	if (!str)
		return (NULL);
	y = count_ec_strs(str);
	if (y < 1)
		return (NULL);
	s = ft_calloc(y + 1, sizeof(char *));
	if (!s)
		return (NULL);
	while (x < y)
	{
		pa = ec_split(str, pa);
		s[x] = ft_substr(str, pb, pa - pb);
		if (!s[x])
			return (ft_free_2d(s), NULL);
		pb = pa;
		x++;
	}
	return (s);
}

char	**xpand_exit(char **s, t_pipex *p)
{
	int	i;

	i = 0;
	if (!s)
		return (NULL);
	while (s[i])
	{
		if (ft_strcmp_bool(s[i], "$?"))
		{
			free(s[i]);
			s[i] = NULL;
			s[i] = ft_itoa_long(p->status);
		}
		i++;
	}
	return (s);
}

char	**xpd_ec(char **s, t_pipex *p)
{
	int		x;
	char	**s1;
	char	**s2;

	x = 0;
	s1 = NULL;
	s2 = NULL;
	if (!s)
		return (NULL);
	while (s[x])
	{
		if (!s_out_q(s[x]) && !ft_strchr(s[x], '=') && (ft_strchr(s[x], '$') && ft_strchr(s[x], '?')))
			s1 = xpd_ec_split(s[x]);
		else
		{
			s1 = ft_calloc(2, sizeof(char *));
			if (!s1)
				return (NULL);
			s1[0] = ft_strdup(s[x]);
			if (!s1[0])
				return (ft_free_2d(s2), ft_free_2d(s), NULL);
		}
		s2 = arrjoin(s2, s1);
		x++;
	}
	ft_free_2d(s);
	return (reformat(xpand_exit(s2, p)));
}
