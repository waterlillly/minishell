/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbaumeis <lbaumeis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 16:41:15 by lbaumeis          #+#    #+#             */
/*   Updated: 2024/07/25 13:25:44 by lbaumeis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

 #ifndef BUFFER_SIZE
 # define BUFFER_SIZE 1
 #endif

# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <stddef.h>
# include <string.h>
# include <ctype.h>
# include <stdarg.h>

int		ft_isascii(int c);
int		ft_isprint(int c);
int		ft_isalpha(int c);
int		ft_isdigit(int c);
int		ft_isalnum(int c);
int		ft_tolower(int c);
int		ft_toupper(int c);
int		ft_atoi(const char *nptr);
size_t	ft_strlen(const char *s);
size_t	ft_strlcpy(char *dst, const char *src, size_t size);
size_t	ft_strlcat(char *dst, const char *src, size_t size);
char	*ft_strchr(const char *s, int c);
char	*ft_strrchr(const char *s, int c);
char	*ft_strnstr(const char *big, const char *little, size_t len);
char	*ft_strdup(const char *s);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
int		ft_memcmp(const void *s1, const void *s2, size_t n);
void	*ft_memset(void *s, int c, size_t n);
void	ft_bzero(void *s, size_t n);
void	*ft_memcpy(void *dest, const void *src, size_t n);
void	*ft_memmove(void *dest, const void *src, size_t n);
void	*ft_memchr(const void *s, int c, size_t n);
void	*ft_calloc(size_t xnmemb, size_t size);
char	*ft_substr(const char *s, unsigned int start, size_t len);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_strjoin_free_both(char *s1, char *s2);
char	*ft_strjoin_free_one(char *s1, const char *s2);
char	*ft_strtrim(char const *s1, char const *set);
void	ft_striteri(char *s, void (*f)(unsigned int, char*));
void	ft_putchar_fd(char c, int fd);
void	ft_putstr_fd(char *s, int fd);
void	ft_putendl_fd(char *s, int fd);
void	ft_putnbr_fd(int c, int fd);
char	**ft_split(char const *s, char c);
char	*ft_itoa(int n);
char	*ft_strmapi(char const *s, char (*f)(unsigned int, char));
int		ft_printf(const char *format, ...);
int		ft_printchar(int c);
int		ft_printstr(char *s);
int		ft_printnbr(char specifier, long int nbr, int base);
int		ft_printptr(void *ptr);
int		ft_decideformat(va_list args, const char *format, int i);
int		ft_strcmp(const char *s1, const char *s2);
int		ft_white(const char *s);
double	ft_atof(char *s);
int		ft_isalpha_extend(int n);
int		ft_isprint_extend(int n);
int		ft_isascii_extend(int n);

/*GET_NEXT_LINE*/
char	*get_next_line(int fd);
char	*ft_buf(char *buf, int *x);
char	*ft_next(char *buf, int fd);
char	*ft_rest(int x, char *buf);

#endif

/*
INPUT CHECK:
			ft_atof
			ft_atoi
			ft_memset

REWRITE AND ADD:
			ft_dtoa
			ft_isdouble
TEST:
			ft_strjoin
*/