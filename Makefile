# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lbaumeis <lbaumeis@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/08/07 16:33:47 by lbaumeis          #+#    #+#              #
#    Updated: 2024/09/18 14:45:47 by lbaumeis         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc
CFLAGS = -Wall -Werror -Wextra -g

.c.o:
	$(CC) $(CFLAGS) -c $< -o $@

CFILES += main.c more_cmds.c exit.c execute.c start.c signals.c pre_exec.c redir.c

CFILES += buildins/utils.c buildins/cd.c buildins/cd_find_path.c buildins/pwd.c #buildins/backup.c
CFILES += buildins/env.c buildins/echo.c buildins/echo_split.c buildins/quotes.c buildins/sorting.c
CFILES += buildins/xpand.c buildins/xport.c buildins/set_export.c buildins/unset.c

CFILES += pipex/pipex.c pipex/error.c pipex/init.c

CFILES += lexparse/minishell.c lexparse/remove_q.c lexparse/quote_count.c lexparse/open_quotes.c
CFILES += lexparse/split_shell.c lexparse/lexer.c lexparse/get_line_cnc.c lexparse/check_syntax.c
CFILES += lexparse/skip_q.c lexparse/parser.c lexparse/set.c lexparse/is_oq.c

OFILES = $(CFILES:.c=.o)
NAME = minishell

#NUMTH = $(shell nproc)
#MAKEFLAGS += --jobs=$(NUMTH)

all: $(NAME)

$(NAME): $(OFILES)
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
	rm -f $(NAME)
	rm -f out
	rm -f hd
	rm -f buildins.h.gch

re: fclean
	$(MAKE) all

mval: re
	($(MAKE) -C libft clean)
	rm -f $(OFILES)
	rm -f out
	rm -f hd
	rm -f buildins.h.gch
	rm -f vgcore.*
	valgrind -s --show-leak-kinds=all --track-fds=yes --leak-check=full --track-origins=yes --suppressions=.vgignore ./$(NAME)

.PHONY: all clean fclean re mval