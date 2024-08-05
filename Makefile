# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: codespace <codespace@student.42.fr>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/07/29 17:21:13 by codespace         #+#    #+#              #
#    Updated: 2024/08/05 11:53:31 by codespace        ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	minishell
CFLAGS	=	-Wall -Wextra -Werror
LIBFT	=	cd srcs/libft
LIBFT_A =	srcs/libft/libft.a
SRC		=	minishell.c \
			error.c \
			remove_q.c \
			quote_count.c \
			open_quotes.c
SRCS	=	${addprefix ${PRE}, ${SRC}}
OBJS	=	${SRCS:.c=.o}
PRE		=	./srcs/
RM		=	rm -f

${NAME}:	${OBJS}
			@${LIBFT} && make all
			cc ${CFLAGS} ${SRCS} -o ${NAME} ${LIBFT_A} -lreadline

all:		${NAME}

clean: 
			@${LIBFT} && make clean
			${RM} ${OBJS}

fclean: 	clean
			@${LIBFT} && make fclean
			${RM} ${NAME}

re:			fclean all

.PHONY:		all clean fclean re