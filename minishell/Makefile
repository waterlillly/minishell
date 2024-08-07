# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lbaumeis <lbaumeis@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/08/06 18:59:20 by lbaumeis          #+#    #+#              #
#    Updated: 2024/08/07 16:15:51 by lbaumeis         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc
CFLAGS = -Wall -Werror -Wextra -g

.c.o:
	$(CC) $(CFLAGS) -c $< -o $@

CFILES = main.c init_mini.c error.c
#CFILES += buildins/utils.c buildins/cd.c buildins/cd_find_path.c
#CFILES += buildins/pwd.c buildins/env.c buildins/echo.c
#CFILES += buildins/xpand.c buildins/xport.c buildins/set_export.c
#CFILES += buildins/utils2.c buildins/add_export.c buildins/unset.c
#CFILES += pipex/pipex.c pipex/close_free.c pipex/init.c pipex/processes.c
#CFILES += pipex/here_doc.c pipex/extra_cases.c
CFILES += par_lex/minishell.c par_lex/remove_q.c
CFILES += par_lex/quote_count.c par_lex/open_quotes.c

OFILES = $(CFILES:.c=.o)

P_NAME = minishell

all: $(P_NAME)

$(P_NAME): $(OFILES)
	($(MAKE) -C libftultra)
	$(CC) $(CFLAGS) -o $@ $^ libftultra/libftultra.a -lreadline
	rm -f out
	rm -f hd
	rm -f buildins.h.gch

clean:
	($(MAKE) -C libftultra clean)
	rm -f $(OFILES)
	rm -f out
	rm -f hd
	rm -f buildins.h.gch

fclean: clean
	($(MAKE) -C libftultra fclean)
	rm -f $(P_NAME)
	rm -f out
	rm -f hd
	rm -f buildins.h.gch

re: fclean all

.PHONY: all clean fclean re