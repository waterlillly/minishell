/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_split.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbaumeis <lbaumeis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/31 17:54:22 by lbaumeis          #+#    #+#             */
/*   Updated: 2024/10/03 14:44:52 by lbaumeis         ###   ########.fr       */
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
	char	**sp3;
	int		x;

	if (!xpd1)
		return (NULL);
	sp1 = NULL;
	sp2 = NULL;
	sp3 = NULL;
	x = 0;
	while (xpd1[x])
	{
		//printf("xpd1[%d]: %s\n", x, xpd1[x]);
		if (!s_out_q(xpd1[x]) && !d_out_q(xpd1[x]) && !ft_strchr(xpd1[x], '='))
			sp1 = xpd_1_split(xpd1[x], ' ');
		else
		{
			sp1 = ft_calloc(2, sizeof(char *));
			if (!sp1)
				return (NULL);
			*sp1 = ft_strdup(xpd1[x]);
		}
		sp2 = arrjoin(sp2, sp1);
		x++;
	}
	x = 0;
	while (sp2[x])
	{
		//printf("sp2[%d]: %s\n", x, sp2[x]);
		if (!s_out_q(sp2[x]) && !d_out_q(sp2[x]))
			sp1 = xpd_2_split(sp2[x], '$');
		else
		{
			sp1 = ft_calloc(2, sizeof(char *));
			if (!sp1)
				return (NULL);
			*sp1 = ft_strdup(sp2[x]);
		}
		sp3 = arrjoin(sp3, sp1);
		if (!sp2[x + 1])
			return (sp3);
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

char	**rewrite(char **s, int c)
{
	int		i;
	int		j;
	char	**arr;
	
	i = 0;
	j = 0;
	arr = NULL;
	arr = ft_calloc(c + 1, sizeof(char *));
	if (!arr)
		return (NULL);
	while (s[i])
	{
		if (s[i] && s[i + 1] && s[i + 2] && ((ft_strcmp_bool(s[i], "\'")
			&& ft_strcmp_bool(s[i + 2], "\'"))
			|| (ft_strcmp_bool(s[i], "\"") && ft_strcmp_bool(s[i + 2], "\""))))
		{
			arr[j] = ft_strjoin(ft_strjoin(s[i], s[i + 1]), s[i + 2]);
			j++;
			i += 3;
		}
		else
		{
			arr[j] = ft_strdup(s[i]);
			j++;
			i++;
		}
	}
	return (ft_free_double(s), arr);
}

char	**reformat(char **s)
{
	int		i;
	int		c;

	i = 0;
	c = ft_arrlen(s);
	while (s[i])
	{
		if (s[i] && s[i + 1] && s[i + 2] && ((ft_strcmp_bool(s[i], "\'")
			&& ft_strcmp_bool(s[i + 2], "\'"))
			|| (ft_strcmp_bool(s[i], "\"") && ft_strcmp_bool(s[i + 2], "\""))))
		{
			c -= 2;
			i += 3;
		}
		else
			i++;
	}
	return (rewrite(s, c));
}

char	**xpd_1(t_minishell_p *pars, int i)
{
	char	**s_q;
	int		x;
	char	**dq1;
	char	**dq2;

	if (!pars)
		return (NULL);
	dq1 = NULL;
	dq2 = NULL;
	s_q = NULL;
	if ((!only_quotes(pars->str[i]) && !d_out_q(pars->str[i])
		&& !ft_strchr(pars->str[i], '='))
		|| (only_quotes(pars->str[i]) && pars->str[i][0] != '\"'))
		s_q = xpd_1_split(pars->str[i], '\'');
	else
	{
		s_q = ft_calloc(2, sizeof(char *));
		if (!s_q)
			return (NULL);
		*s_q = ft_strdup(pars->str[i]);
	}
	if (!s_q)
		return (NULL);
	x = 0;
	s_q = reformat(s_q);
	while (s_q[x])
	{
		//printf("s_q[%d]: %s\n", x, s_q[x]);
		if (!s_out_q(s_q[x]) && !ft_strchr(s_q[x], '='))
			dq1 = xpd_1_split(s_q[x], '\"');
		else
		{
			dq1 = ft_calloc(2, sizeof(char *));
			if (!dq1)
				return (NULL);
			*dq1 = ft_strdup(s_q[x]);
		}
		dq2 = arrjoin(dq2, dq1);
		x++;
	}
	dq2 = reformat(dq2);
	return (dq2);
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
			tmp = xpd_2(xpd_1(pars, i));
			j = 0;
			while (tmp[j])
			{
				pars->ps[i] = ft_strjoin_free_one(pars->ps[i], xpand(p, tmp, j));
				//puts(pars->ps[i]);
				j++;
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