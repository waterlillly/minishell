# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lbaumeis <lbaumeis@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/06/13 06:42:03 by lbaumeis          #+#    #+#              #
#    Updated: 2024/07/29 13:26:15 by lbaumeis         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc
CFLAGS = -Wall -Werror -Wextra -g

.c.o:
	$(CC) $(CFLAGS) -c $< -o $@

CFILES_PIPEX += ../execution/pipex/pipex.c ../execution/pipex/error.c
CFILES_PIPEX += ../execution/pipex/init.c ../execution/pipex/processes.c 
CFILES_PIPEX += ../execution/pipex/check.c ../execution/pipex/here_doc.c
CFILES_PIPEX += ../execution/pipex/extra_cases.c
CFILES_BUILDINS += ../execution/buildins/buildins_init.c ../execution/buildins/err_or.c
CFILES_BUILDINS += ../execution/buildins/home.c ../execution/buildins/menvp.c ../execution/buildins/pwd.c
CFILES_BUILDINS += ../execution/buildins/menv.c ../execution/buildins/cdpath.c ../execution/buildins/get_env.c
CFILES = main.c $(CFILES_PIPEX) $(CFILES_BUILDINS)
OFILES = $(CFILES:.c=.o)
P_NAME = minishell

all: $(P_NAME)

$(P_NAME): $(OFILES)
	($(MAKE) -C ../libft)
	$(CC) $(CFLAGS) -o $@ $^ ../libft/libft.a -lreadline
	rm -f out
	rm -f hd
	rm -f buildins.h.gch

clean:
	($(MAKE) -C ../libft clean)
	rm -f $(OFILES)
	rm -f out
	rm -f hd
	rm -f buildins.h.gch

fclean: clean
	($(MAKE) -C ../libft fclean)
	rm -f $(P_NAME)
	rm -f out
	rm -f hd
	rm -f buildins.h.gch

re: fclean all

.PHONY: all clean fclean re
