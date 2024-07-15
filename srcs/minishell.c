#include <stdio.h>
#include "get_next_line.h"
#include "./libft/libft.h"

int	main(void)
{
	int				in;
	static char		*line[2];
	while (1)
	{
		ft_putstr_fd("this is a legit minishell $>", 1);
		in = get_next_line(0, line);
		
		if (!ft_strncmp("done", line[0], 4))
			return (free(line[0]), 0);
		ft_putendl_fd(line[0], 1);
	}
}