#include <fcntl.h>
#include <stdio.h>
#include "./srcs/get_next_line.h"

int	main(void)
{
	char *line[20];
	int	fd1;
	int	fd2;
	int	fd3;
	fd2 = open("abc", O_RDONLY);
	fd3 = open("'file1'$'\n\n\n\n'", O_RDONLY);
	printf("%d, %d, %d", fd1, fd2, fd3);
	get_next_line(fd1, line);
	printf("%s", line[0]);
	// get_next_line(fd2, line);
	// get_next_line(fd3, line);
	// printf("%s, %s, %s", line[fd1], line[fd2], line[fd3]);
}