# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lbaumeis <lbaumeis@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/07/27 14:21:08 by lbaumeis          #+#    #+#              #
#    Updated: 2024/07/29 15:38:51 by lbaumeis         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc
CFLAGS = -Wall -Werror -Wextra -g

.c.o:
	$(CC) $(CFLAGS) -c $< -o $@

CFILES = main.c buildins_init.c err_or.c home.c menvp.c pwd.c menv.c cdpath.c get_env.c
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