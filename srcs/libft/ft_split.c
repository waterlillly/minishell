/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 18:25:17 by codespace         #+#    #+#             */
/*   Updated: 2023/09/20 16:09:51 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

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
