/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_split.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbaumeis <lbaumeis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/31 17:54:22 by lbaumeis          #+#    #+#             */
/*   Updated: 2024/10/01 16:59:49 by lbaumeis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	count_dlr_strs(char *s, char c)
{
	int	counter;
	int	x;

	counter = 0;
	x = 0;
	while (s[x])
	{
		if (s[x] == c)
		{
			x++;
			if (s[x] == c || s[x] == '\0')
			{
				x++;
				counter++;
			}
		}
		else
		{
			while (s[x] && s[x] != c)
				x++;
			counter++;
		}
	}
	return (counter);
}

int	count_q_strs(char *str, int q)
{
	int	c;
	int	x;

	c = 0;
	x = 0;
	while (str[x])
	{
		if (str[x] == q)
		{
			x++;
			while (str[x] && str[x] != q)
				x++;
			if (str[x] && str[x] == q)
			{
				x++;
				c++;
			}
		}
		else
		{
			while (str[x] && str[x] != q)
				x++;
			c++;
		}
	}
	return (c);
}

int	dlr_split(char *s, int d, int pa)
{
	if (s[pa] && s[pa] == d)
	{
		pa++;
		if (s[pa] && s[pa] == d)
			pa++;
		else
		{
			while (s[pa] && s[pa] != d)
				pa++;
		}
	}
	else
	{
		while (s[pa] && s[pa] != d)
			pa++;
	}
	return (pa);
}

int	q_split(char *s, int q, int pa)
{
	if (s[pa] && s[pa] == q)
	{
		pa++;
		if (s[pa] && s[pa] == q)
			pa++;
		else	
		{
			while (s[pa] && s[pa] != q)
				pa++;
		}
	}
	else
	{
		while (s[pa] && s[pa] != q)
			pa++;
	}
	return (pa);
}

char	**xpd_1_split(char *str, int q)
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
	y = count_q_strs(str, q);
	if (y < 1)
		return (NULL);
	s = ft_calloc(y + 1, sizeof(char *));
	if (!s)
		return (NULL);
	while (x < y)
	{
		pa = q_split(str, q, pa);
		s[x] = ft_substr(str, pb, pa - pb);
		pb = pa;
		x++;
	}
	return (s);
}

char	**xpd_2_split(char *str, int q)
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
	y = count_dlr_strs(str, q);
	if (y < 1)
		return (NULL);
	s = ft_calloc(y + 1, sizeof(char *));
	if (!s)
		return (NULL);
	while (x < y)
	{
		pa = dlr_split(str, q, pa);
		s[x] = ft_substr(str, pb, pa - pb);
		pb = pa;
		x++;
	}
	return (s);
}

char	**xpd_2(char **xpd1)
{
	char	**sp1;
	char	**sp2;
	int		x;
	char	**d1;
	char	**d2;
	char	**tmp;

	if (!xpd1)
		return (NULL);
	sp1 = NULL;
	sp2 = NULL;
	d1 = NULL;
	d2 = NULL;
	x = 0;
	while (xpd1[x])
	{
		if (s_out_q(xpd1[x]) == false)
		{
			sp1 = xpd_1_split(xpd1[x], ' ');
			sp2 = arrjoin(sp2, sp1);
		}
		else
		{
			tmp = NULL;
			tmp = ft_calloc((ft_arrlen(sp2) + 2), sizeof(char *));
			if (!tmp)
				return (NULL);
			while (ft_arrlen(sp2) > 0 && *sp2)
			{
				*tmp = ft_strdup(*sp2);
				tmp++;
				sp2++;
			}
			*tmp = ft_strdup(xpd1[x]);
			//ft_free_double(sp2);
			sp2 = ft_arrdup(tmp);
			//ft_free_double(tmp);
		}
		x++;
	}
	x = 0;
	while (sp2[x])
	{
		if (s_out_q(sp2[x]) == false)
		{
			d1 = xpd_2_split(sp2[x], '$');
			d2 = arrjoin(d2, d1);
			if (!sp2[x + 1])
				return (d2);
		}
		else
		{
			tmp = NULL;
			tmp = ft_calloc((ft_arrlen(d2) + 2), sizeof(char *));
			while (ft_arrlen(d2) > 0 && *d2)
			{
				*tmp = ft_strdup(*d2);
				tmp++;
				sp2++;
			}
			*tmp = ft_strdup(sp2[x]);
			//ft_free_double(sp2);
			sp2 = ft_arrdup(tmp);
			//ft_free_double(tmp);
		}
		x++;
	}
	return (sp2);
}

char	**arrjoin(char **old, char **new)
{
	char	**ret;
	int		x;
	int		y;

	x = 0;
	y = 0;
	ret = ft_calloc((ft_arrlen(old) + ft_arrlen(new) + 1), sizeof(char *));
	if (!ret)
		return (NULL);
	while (ft_arrlen(old) > 0 && old[x])
	{
		ret[x] = ft_strdup(old[x]);
		x++;
	}
	while (ft_arrlen(new) > 0 && new[y])
	{
		ret[x] = ft_strdup(new[y]);
		x++;
		y++;
	}
	return (ft_free_double(old), ft_free_double(new), ret);
}

char	**ft_arrdup(char **s)
{
	int		x;
	char	**arr;

	x = 0;
	if (!s)
		return (NULL);
	arr = ft_calloc(ft_arrlen(s) + 1, sizeof(char *));
	if (!arr)
		return (NULL);
	while (s[x])
	{
		arr[x] = ft_strdup(s[x]);
		x++;
	}
	return (arr);
}

char	**xpd_1(t_minishell_p *pars, int i)
{
	char	**s_q;
	int		x;
	char	**dq1;
	char	**dq2;
	char	**tmp;

	if (!pars)
		return (NULL);
	dq1 = NULL;
	dq2 = NULL;
	s_q = NULL;
	s_q = xpd_1_split(pars->str[i], '\'');
	if (!s_q)
		return (NULL);
	x = 0;
	while (s_q[x])
	{
		if (s_out_q(s_q[x]) == false)
		{
			dq1 = xpd_1_split(s_q[x], '\"');
			dq2 = arrjoin(dq2, dq1);
		}
		else
		{
			tmp = NULL;
			tmp = ft_calloc((ft_arrlen(dq2) + 2), sizeof(char *));
			while (ft_arrlen(dq2) > 0 && *dq2)
			{
				*tmp = ft_strdup(*dq2);
				tmp++;
				dq2++;
			}
			*tmp = ft_strdup(s_q[x]);
			//ft_free_double(dq2);
			dq2 = ft_arrdup(tmp);
			//ft_free_double(tmp);
		}
		x++;
	}
	return (dq2);
}

void	xpd(t_pipex *p, t_minishell_p *pars)
{
	int				i;
	int				j;
	char			**tmp;
	

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
			tmp = xpd_2(xpd_1(pars, i));
			if (ft_arrlen(tmp) > 0)
			{
				j = 0;
				while (tmp[j])
				{
					pars->ps[i] = ft_strjoin_free_both(pars->ps[i], xpand(p, tmp, j));
					j++;
				}
			}
			ft_free_double(tmp);
			i++;
		}
		pars = pars->next;
	}
}

/*

echo "hi"''hello$HOME'""' $$$fuck'hello$hello$$$PWD$'""

//SQ
"hi"
''
hello$HOME
'""'
 $$$fuck
'hello$hello$$$PWD$'
""

//DQ
"hi"
''
hello$HOME
'""'--->add check if in single q: return
 $$$fuck
'hello$hello$$$PWD$'
""

//SPC
"hi"
''
hello$HOME
'""'
{ }
$$$fuck
'hello$hello$$$PWD$'
""

//DLR
"hi"
''
hello
$HOME
'""'
{ }
$$
$fuck
'hello$hello$$$PWD$'--->add check if in single q: return
""

*/

/*
int	countstrs(char *s, char c)
{
	int	counter;
	int	x;

	counter = 0;
	x = 0;
	while (s[x])
	{
		if (s[x] == c)
		{
			x++;
			if (s[x] == c || s[x] == '\0')
			{
				x++;
				counter++;
			}
		}
		else
		{
			while (s[x] && s[x] != c)
				x++;
			counter++;
		}
	}
	return (counter);
}

int	do_split(char *s, char c, int pos_a)
{
	if (s[pos_a] && s[pos_a] == c)
	{
		pos_a++;
		if (s[pos_a] && s[pos_a] == c)
			pos_a++;
		else
		{
			while (s[pos_a] && s[pos_a] != c)
				pos_a++;
		}
	}
	else
	{
		while (s[pos_a] && s[pos_a] != c)
		pos_a++;
	}
	return (pos_a);
}

char	**echo_split(char *s, int c)
{
	int		pos_a;
	int		pos_b;
	int		x;
	int		y;
	char	**result;

	pos_a = 0;
	pos_b = 0;
	x = 0;
	if (!s)
		return (NULL);
	y = countstrs(s, c);
	if (y < 1)
		return (NULL);
	result = ft_calloc(countstrs(s, c) + 1, sizeof(char *));
	if (!result)
		return (NULL);
	while (x < countstrs(s, c))
	{
		pos_a = do_split(s, c, pos_a);
		result[x] = ft_substr(s, pos_b, pos_a - pos_b);
		if (!result[x])
			return (ft_free_double(result), NULL);
		pos_b = pos_a;
		x++;
	}
	return (result);
}
*/