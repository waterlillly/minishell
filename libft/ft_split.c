/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbaumeis <lbaumeis@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/01 18:17:03 by lbaumeis          #+#    #+#             */
/*   Updated: 2024/08/14 15:50:24 by lbaumeis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_countstrs(char const *s, char c)
{
	int	counter;

	counter = 0;
	if (!s)
		return (0);
	while (*s)
	{
		while (*s == c && *s)
			s++;
		if (*s)
			counter++;
		while (*s != c && *s)
			s++;
	}
	return (counter);
}

static int	ft_place(char const *s, char c, int last_pos)
{
	while (s[last_pos] != '\0' && s[last_pos] != c)
		last_pos++;
	return (last_pos);
}

char	**ft_split(char const *s, char c)
{
	char	**result;
	int		x;
	int		last_pos;

	last_pos = 0;
	result = malloc((ft_countstrs(s, c) + 1) * sizeof(char *));
	if (!s || !result)
		return (NULL);
	x = 0;
	while (x < ft_countstrs(s, c))
	{
		while (s[last_pos] == c)
			last_pos++;
		result[x] = ft_substr(s, last_pos, ft_place(s, c, last_pos) - last_pos);
		if (!result[x++])
		{
			while (x > 0)
				free(result[--x]);
			free(result);
			return (NULL);
		}
		last_pos = ft_place(s, c, last_pos + 1);
	}
	result[x] = NULL;
	return (result);
}

/*
static int	count(char *str, char charset)
{
	int		len_sub;
	int		len_sep;
	int		i;

	len_sub = 0;
	len_sep = 0;
	i = 0;
	while (str[len_sub + len_sep])
	{
		while ((charset == str[len_sub + len_sep])
			&& str[len_sub + len_sep])
			len_sep++;
		if ((charset != str[len_sub + len_sep])
			&& str[len_sub + len_sep])
			i++;
		while ((charset != str[len_sub + len_sep])
			&& str[len_sub + len_sep])
			len_sub++;
	}
	return (i);
}

static char	*skip(char *str, char charset, int *len)
{
	int	i;

	i = 0;
	*len = 0;
	while (charset == *str && *str)
		str++;
	while ((charset != str[i]) && str[i])
	{
		*len = *len + 1;
		i++;
	}
	return (str);
}

static char	**set_free(char **out, int i)
{
	while (--i >= 0)
		free(out[i]);
	free(out);
	return (NULL);
}

char	**ft_split(char const *s, char c)
{
	int		len;
	char	**out;
	int		i;
	int		a;
	char	*str_temp;

	str_temp = (char *)s;
	len = 0;
	i = -1;
	a = 0;
	if (s == NULL)
		return (NULL);
	out = (char **)malloc((count(str_temp, c) + 1) * sizeof(char *));
	if (!out)
		return (out);
	while (++i < count(str_temp, c))
	{
		a = (int)(skip((char *)(s + len + a), c, &len) - s);
		out[i] = (char *)malloc((len + 1) * sizeof(char));
		if (!out[i])
			return (set_free(out, i));
		ft_strlcpy(out[i], (char *)(s + a), len + 1);
	}
	out[i] = NULL;
	return (out);
}
*/

/*
int main(void)
{
    char const 	*s = "1  22   333    4444     55555                 ";
    char       	c = ' ';
    char       	**split = ft_split(s, c);
    int        	i = 0;
	
	while (i <= ft_countstrs(s, c))
    {
        printf("[%s]\n", split[i]);
        i++;
    }
	if (!split)
		{
			while (split && i >= 0)
				free(split[i--]);
			free(split);
		}
	// ft_free(split, (i+1));
    return (0);
}
*/
