/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaleman <jaleman@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/26 07:11:59 by jaleman           #+#    #+#             */
/*   Updated: 2016/12/21 08:39:49 by jaleman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

/*
** Needed for malloc(), free() and write(). Also for typedef size_t and sizeof()
*/

# include <unistd.h>
# include <stdlib.h>

/*
** Macro for the buffer size, the max number of file descriptors available, and
** to get the correct return value from the gnl_read_file() function.
** Find the max number of files:
** Mac: launchctl limit maxfiles
** Linux: ulimit -n
*/

# define BUFF_SIZE 8
# define MAX_FD 1024 + 1
# define RET_VALUE(ret)	ret > 0 ? 1 : ret

/*
** Prototype for the get_next_line() function.
*/

int		get_next_line(int const fd, char **line);

#endif
