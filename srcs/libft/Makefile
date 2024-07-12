# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: codespace <codespace@student.42.fr>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/07/27 22:04:26 by mgardesh          #+#    #+#              #
#    Updated: 2023/09/18 10:30:41 by codespace        ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC			= ft_bzero.c ft_isalnum.c ft_isalpha.c ft_isascii.c ft_isdigit.c ft_isprint.c ft_memcpy.c ft_memmove.c ft_memset.c ft_strchr.c ft_strlcat.c ft_strlcpy.c ft_strlen.c ft_strrchr.c ft_tolower.c ft_toupper.c ft_memchr.c ft_strncmp.c ft_memcmp.c ft_strnstr.c ft_atoi.c ft_strdup.c ft_calloc.c ft_strjoin.c ft_substr.c ft_strtrim.c ft_itoa.c ft_split.c ft_strmapi.c ft_striteri.c ft_putchar_fd.c ft_putstr_fd.c ft_putendl_fd.c ft_putnbr_fd.c

SRC_B		= ft_lstnew.c ft_lstadd_front.c ft_lstsize.c ft_lstlast.c ft_lstadd_back.c ft_lstdelone.c ft_lstclear.c ft_lstiter.c ft_lstmap.c

SRCS		= ${addprefix ${PRE}, ${SRC}}

SRCS_B		= ${addprefix ${PRE}, ${SRC_B}}

OBJS		= ${SRCS:.c=.o}

OBJS_B		= ${SRCS_B:.c=.o}

PRE			= ./

HEAD		= ./

NAME		= libft.a

LIBC		= ar rc

LIBR		= ranlib

RM			= rm -f

GCC			= cc

CFLAGS		= -Wall -Wextra -Werror

all:			${NAME}

.c.o:
			${GCC} ${CFLAGS} -c -I ${HEAD} $< -o ${<:.c=.o}

${NAME}:	${OBJS}
			${LIBC} ${NAME} ${OBJS}
			${LIBR} ${NAME}


clean:
			rm -f ${OBJS}

fclean:		clean
			rm -f ${NAME}
			rm -f ${OBJS_B}
			rm -f libft.so
			rm -f a.out

re:			fclean all

bonus:			${OBJS} $(OBJS_B)
				ar rcs $(NAME) $(OBJS) $(OBJS_B)

.PHONY:		all clean fclean re
