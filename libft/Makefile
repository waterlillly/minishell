# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lbaumeis <lbaumeis@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/08/06 18:13:23 by lbaumeis          #+#    #+#              #
#    Updated: 2024/09/18 14:48:23 by lbaumeis         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CFILES = ft_isalpha.c ft_isdigit.c ft_isalnum.c ft_isascii.c ft_isprint.c
CFILES += ft_strlen.c ft_memset.c ft_bzero.c ft_memcpy.c ft_memmove.c
CFILES += ft_strlcpy.c ft_strlcat.c ft_toupper.c ft_tolower.c ft_strchr.c
CFILES += ft_strrchr.c ft_strncmp.c ft_memchr.c ft_memcmp.c ft_strnstr.c
CFILES += ft_atoi.c ft_calloc.c ft_strdup.c ft_substr.c ft_strjoin.c
CFILES += ft_strtrim.c ft_striteri.c ft_putchar_fd.c ft_putstr_fd.c
CFILES += ft_putendl_fd.c ft_putnbr_fd.c ft_split.c ft_itoa.c ft_strmapi.c
CFILES += ft_printf.c ft_printchar.c ft_printstr.c ft_printnbr.c ft_printptr.c
CFILES += ft_decideformat.c ft_strcmp.c ft_white.c ft_atof.c ft_str_upper.c
CFILES += ft_isalpha_extend.c ft_isprint_extend.c ft_isascii_extend.c
CFILES += get_next_line.c ft_strjoin_free_both.c ft_strjoin_free_one.c
CFILES += ft_str_lower.c ft_arrlen.c ft_free_double.c ft_print_array.c
CFILES += ft_strcmp_bool.c ft_strnstr_bool.c ft_atoi_long.c ft_itoa_long.c
CFILES += ft_lstnew.c ft_lstadd_front.c ft_lstsize.c ft_lstlast.c 
CFILES += ft_lstadd_back.c ft_lstdelone.c ft_lstclear.c ft_lstiter.c ft_lstmap.c
CFILES += ft_strcat.c ft_strlen_2d.c ft_realloc_2d.c ft_free_2d.c ft_strncpy.c

OFILES = $(CFILES:.c=.o)

CC = cc
CFLAGS = -Wall -Wextra -Werror
NAME = libft.a

NUMTH = $(shell nproc)
MAKEFLAGS += --jobs=$(NUMTH)

.c.o:
	$(CC) $(CFLAGS) -c $< -o $@

all: $(NAME)

$(NAME): $(OFILES)
	ar rc $(NAME) $(OFILES) 
	ranlib $(NAME)

clean:
	rm -f $(OFILES)

fclean: clean
	rm -f $(NAME)
	rm -f a.out

re: fclean
	$(MAKE) all
	
.PHONY: all clean fclean re