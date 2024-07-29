#include <pipex.h>

int	find_dollar(char *s)
{
	int	i;

	i = 0;
	if (!s)
		return (-1);
	while (s[i])
	{
		if (s[i] == '$')
			return (i);
		i++;
	}
	return (-1);
}

void	create_line(char **line, t_args arg, t_strs *str, int *pipes)
{
	int	dollar_ind;
	int	length;

	dollar_ind = find_dollar(*line);
	while (dollar_ind != -1)
	{
		length = 0;
		str->until_dlr = ft_substr(*line, 0, dollar_ind);
		str->tmp = until_whitespc(*line + dollar_ind + 1, &length);
		err_pipe (!str->tmp || !str->until_dlr, pipes, arg);
		str->ret = strjoin_w_free(str->ret, str->until_dlr);
		err_pipe (!str->ret, pipes, arg);
		if (!*str->tmp)
			*line += dollar_ind + length + 1;
		else
			*line += dollar_ind + ft_strlen(str->tmp) + 1;
		str->ret = strjoin_w_free(str->ret, check_env(str->tmp, arg.envp, length));
		err_pipe (!str->ret, pipes, arg);
		free(str->until_dlr);
		free(str->tmp);
		dollar_ind = find_dollar(*line);
	}
	str->ret = strjoin_w_free(str->ret, *line);
	err_pipe (!str->ret, pipes, arg);
}

char	*expand(char *line, t_args arg, int *pipes)
{
	int		dollar_ind;
	t_strs	str;

	dollar_ind = find_dollar(line);
	if (dollar_ind == -1)
		return (line);
	str.to_free = line;
	str.ret = NULL;
	create_line(&line, arg, &str, pipes);
	free(str.to_free);
	return (str.ret);
}

char	*until_eq(char *s)
{
	char	*ret;
	int		i;

	i = 0;
	while (s[i] != '=')
		i++;
	ret = malloc(sizeof(char) * (i + 1));
	if (!ret)
		return (ret);
	i = 0;
	while (*s != '=')
		ret[i++] = *s++;
	ret[i] = 0;
	return (ret);
}

char	*after_eq(char *s)
{
	int	i;

	i = 0;
	while (s[i] != '=')
		i++;
	i++;
	return (s + i);
}

char	*strjoin_w_free(char*s1, char *s2)
{
	size_t	len1;
	size_t	len2;
	int		i;
	int		k;
	char	*s;

	if (!s1)
		return (ft_strdup(s2));
	i = -1;
	k = 0;
	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	s = malloc (sizeof(char) * (len1 + len2 + 1));
	if (!s)
		return (s);
	while (++i < (int)(len1 + len2))
	{
		if (i < (int)len1)
			s[i] = s1[i];
		else
			s[i] = s2[k++];
	}
	s[i] = 0;
	free(s1);
	return (s);
}

int	check_varname(char *s)
{
	while (*s && !ft_isspace(*s) && *s != '$')
	{
		if (!ft_isdigit(*s) && *s != '_' && !ft_isalpha(*s))
			return (1);
		s++;
	}
	return (0);
}

char	*until_whitespc(char *s, int *length)
{
	char	*ret;
	int		i;

	i = 0;
	while (s[i] && !ft_isspace(s[i]) && s[i] != '$')
		i++;
	if (ft_isdigit(*s) || check_varname(s))
	{
		*length = i;
		return (ft_strdup(""));
	}
	ret = malloc(sizeof(char) * (i + 1));
	if (!ret)
		return (ret);
	i = 0;
	while (s[i] && !ft_isspace(s[i]) && s[i] != '$')
	{
		ret[i] = s[i];
		i++;
	}
	ret[i] = 0;
	return (ret);
}

char	*check_env(char *line, char **env, int length)
{
	char	*tmp;
	int		i;

	i = 0;
	if (!*line && length == 0)
		return ("$");
	while (env[i])
	{
		tmp = until_eq(env[i]);
		if (!ft_strcmp(tmp, line))
		{
			free(tmp);
			return (after_eq(env[i]));
		}
		free(tmp);
		i++;
	}
	return ("");
}