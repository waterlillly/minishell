# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lbaumeis <lbaumeis@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/08/07 16:33:47 by lbaumeis          #+#    #+#              #
#    Updated: 2024/08/07 22:10:16 by lbaumeis         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc
CFLAGS = -Wall -Werror -Wextra -g

.c.o:
	$(CC) $(CFLAGS) -c $< -o $@

CFILES += main.c more_cmds.c exit.c more_cmds.c
CFILES += buildins/utils.c buildins/cd.c buildins/cd_find_path.c buildins/pwd.c buildins/env.c buildins/echo.c
CFILES += buildins/xpand.c buildins/xport.c buildins/set_export.c buildins/utils2.c buildins/add_export.c buildins/unset.c
CFILES += pipex/pipex.c pipex/error.c pipex/init.c pipex/processes.c pipex/check.c pipex/here_doc.c pipex/extra_cases.c
OFILES = $(CFILES:.c=.o)
P_NAME = exec

all: $(P_NAME)

$(P_NAME): $(OFILES)
	($(MAKE) -C libft)
	$(CC) $(CFLAGS) -o $@ $^ libft/libft.a -lreadline
	rm -f out
	rm -f hd
	rm -f buildins.h.gch

clean:
	($(MAKE) -C libft clean)
	rm -f $(OFILES)
	rm -f out
	rm -f hd
	rm -f buildins.h.gch

fclean: clean
	($(MAKE) -C libft fclean)
	rm -f $(P_NAME)
	rm -f out
	rm -f hd
	rm -f buildins.h.gch

re: fclean all

.PHONY: all clean fclean re