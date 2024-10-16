/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xpd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbaumeis <lbaumeis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/06 17:41:15 by lbaumeis          #+#    #+#             */
/*   Updated: 2024/10/15 15:04:52 by lbaumeis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*DOLLAR*/
char	**xpd_dollar(char **s)
{
	char	**s1;
	char	**s2;
	int		x;

	if (!s)
		return (NULL);
	s1 = NULL;
	s2 = NULL;
	x = 0;
	while (s[x])
	{
		if (!s_out_q(s[x]) && !d_out_q(s[x]))
			s1 = xpd_2_split(s[x], '$');
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
	return (s2);
}

/*SPACE*/
char	**xpd_space(char **s)
{
	int		x;
	char	**s1;
	char	**s2;

	x = 0;
	s1 = NULL;
	s2 = NULL;
	while (s[x])
	{
		if (!s_out_q(s[x]) && !ft_strchr(s[x], '=') && !d_out_q(s[x]) && ft_strchr(s[x], ' '))
			s1 = xpd_1_split(s[x], ' ');
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
	return (s2);
}

/*SINGLE QUOTES*/
char	**xpd_single(char **s)
{
	int		x;
	char	**s1;
	char	**s2;
	
	x = 0;
	s1 = NULL;
	s2 = NULL;
	while (s[x])
	{
		if ((!only_quotes(s[x]) && !ft_strchr(s[x], '=') && !d_out_q(s[x]))
		|| (only_quotes(s[x]) && (s[x][0] != '\"')))
			s1 = xpd_1_split(s[x], '\'');
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
	return (reformat(s2));
}

/*DOUBLE QUOTES*/
char	**xpd_double(char **s)
{
	int		x;
	char	**d1;
	char	**d2;
	
	x = 0;
	d1 = NULL;
	d2 = NULL;
	while (s[x])
	{
		if (!s_out_q(s[x]) && !ft_strchr(s[x], '=') && !s_out_q(s[x]))// && s[x][0] != '\'')
			d1 = xpd_1_split(s[x], '\"');
		else
		{
			d1 = ft_calloc(2, sizeof(char *));
			if (!d1)
				return (NULL);
			d1[0] = ft_strdup(s[x]);
			if (!d1[0])
				return (ft_free_2d(d2), ft_free_2d(s), NULL);
		}
		d2 = arrjoin(d2, d1);
		x++;
	}
	ft_free_2d(s);
	return (reformat(d2));
}

char	**xpd_slash(char **s)
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
		if (!s_out_q(s[x]) && !ft_strchr(s[x], '=') && !d_out_q(s[x]))
			s1 = xpd_slash_split(s[x], '/');
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
	return (s2);
}

/*START*/
char	**xpd_start(t_minishell_p *pars, int i)
{
	char	**s;

	if (!pars || !pars->str)
		return (NULL);
	s = NULL;
	if ((!only_quotes(pars->str[i]) && !ft_strchr(pars->str[i], '=') && !d_out_q(pars->str[i]))
		|| (only_quotes(pars->str[i]) && (pars->str[i][0] != '\"')))
		s = xpd_1_split(pars->str[i], '\'');
	else
	{
		s = ft_calloc(2, sizeof(char *));
		if (!s)
			return (NULL);
		s[0] = ft_strdup(pars->str[i]);
		if (!s[0])
			return (ft_free_2d(s), NULL);
	}
	return (reformat(s));
}
