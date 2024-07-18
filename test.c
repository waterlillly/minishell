#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "./srcs/get_next_line.h"

int	is_sep(char *charset, char c)
{
	while (*charset)
	{
		if (*charset == c)
			return (1);
		charset++;
	}
	return (0);
}

int	count(char *str, char *charset)
{
	int		len_sub;
	int		len_sep;
	int		i;
	int		double_q;
	int		single_q;

	len_sub = 0;
	len_sep = 0;
	single_q = 0;
	double_q = 0;
	i = 0;
	while (str[len_sub + len_sep])
	{
		while (is_sep(charset, str[len_sub + len_sep]) 
			&& str[len_sub + len_sep])
			len_sep++;
		if (!is_sep(charset, str[len_sub + len_sep]) 
			&& str[len_sub + len_sep])
			i++;
		while ((!is_sep(charset, str[len_sub + len_sep]) 
			&& str[len_sub + len_sep]) || (single_q % 2 == 1 || double_q % 2 == 1))
		{
			if (str[i] == '\"' && single_q % 2 == 0)
			double_q++;
			if (str[i] == '\'' && double_q % 2 == 0)
			single_q++;
			len_sub++;
		}
	}
	return (i);
}

int	main(int argc, char **argv)
{

	printf("%d, %s, %s, %d\n",argc, argv[1], argv[2], count(argv[1], argv[2]));
}