# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lbaumeis <lbaumeis@student.42vienna.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/07/27 14:21:08 by lbaumeis          #+#    #+#              #
#    Updated: 2024/08/02 21:30:38 by lbaumeis         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc
CFLAGS = -Wall -Werror -Wextra -g

.c.o:
	$(CC) $(CFLAGS) -c $< -o $@

CFILES += main.c utils.c cd.c cdpath.c cd_find_path.c pwd.c env.c echo.c
CFILES += expand.c exp.c
OFILES = $(CFILES:.c=.o)
P_NAME = buildins

all: $(P_NAME)

$(P_NAME): $(OFILES)
	($(MAKE) -C ../../libft)
	$(CC) $(CFLAGS) -o $@ $^ ../../libft/libft.a -lreadline
	rm -f out
	rm -f hd
	rm -f buildins.h.gch

clean:
	($(MAKE) -C ../../libft clean)
	rm -f $(OFILES)
	rm -f out
	rm -f hd
	rm -f buildins.h.gch

fclean: clean
	($(MAKE) -C ../../libft fclean)
	rm -f $(P_NAME)
	rm -f out
	rm -f hd
	rm -f buildins.h.gch

re: fclean all

.PHONY: all clean fclean re