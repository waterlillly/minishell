# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lbaumeis <lbaumeis@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/06/13 06:42:03 by lbaumeis          #+#    #+#              #
#    Updated: 2024/07/26 13:09:24 by lbaumeis         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc
CFLAGS = -Wall -Werror -Wextra -g

.c.o:
	$(CC) $(CFLAGS) -c $< -o $@

CFILES = main.c pipex.c error.c init.c processes.c check.c here_doc.c
CFILES += extra_cases.c
OFILES = $(CFILES:.c=.o)
P_NAME = pipex

all: $(P_NAME)

$(P_NAME): $(OFILES)
	($(MAKE) -C ../../libft)
	$(CC) $(CFLAGS) -o $@ $^ ../../libft/libft.a -lreadline
	rm -f out
	rm -f hd

clean:
	($(MAKE) -C ../../libft clean)
	rm -f $(OFILES)
	rm -f out
	rm -f hd

fclean: clean
	($(MAKE) -C ../../libft fclean)
	rm -f $(P_NAME)
	rm -f out
	rm -f hd

re: fclean all

.PHONY: all clean fclean re
