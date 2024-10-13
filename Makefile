# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lbaumeis <lbaumeis@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/08/07 16:33:47 by lbaumeis          #+#    #+#              #
#    Updated: 2024/10/13 21:52:46 by lbaumeis         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc
CFLAGS = -Wall -Werror -Wextra -g

.c.o:
	$(CC) $(CFLAGS) -c $< -o $@

CFILES += main.c exit.c start.c signals.c free.c

CFILES += exec/utils.c exec/cd.c exec/cd_find_path.c exec/pwd.c
CFILES += exec/env.c exec/echo.c exec/echo_split.c exec/quotes.c exec/sorting.c
CFILES += exec/xpand.c exec/xport.c exec/set_export.c exec/unset.c
CFILES += exec/pipex.c exec/close_pipes.c exec/init.c exec/more_cmds.c
CFILES += exec/pre_exec.c exec/redir.c exec/execute.c exec/xpd_dollar.c
CFILES += exec/xpd_quotes.c exec/xpd_space.c exec/xpd_utils.c exec/xpd.c

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