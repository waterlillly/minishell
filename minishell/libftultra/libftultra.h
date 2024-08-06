/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libftultra.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbaumeis <lbaumeis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 16:53:55 by lbaumeis          #+#    #+#             */
/*   Updated: 2024/08/06 18:28:33 by lbaumeis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFTULTRA_H
# define LIBFTULTRA_H

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
# include <stdbool.h>

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}	t_list;

int		ft_isascii(int c);
int		ft_isprint(int c);
int		ft_isalpha(int c);
int		ft_isdigit(int c);
int		ft_isalnum(int c);
int		ft_tolower(int c);
int		ft_toupper(int c);
int		ft_atoi(const char *nptr);
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
char	*ft_strtrim(char const *s1, char const *set);
void	ft_striteri(char *s, void (*f)(unsigned int, char*));
void	ft_putchar_fd(char c, int fd);
void	ft_putstr_fd(char *s, int fd);
void	ft_putendl_fd(char *s, int fd);
char	**ft_split(char const *s, char c);
char	*ft_itoa(int n);
char	*ft_strmapi(char const *s, char (*f)(unsigned int, char));

/*SAME SAME BUT DIFFERENT*/
//size_t	ft_strlen(const char *s);
//size_t	ft_strlen(const char *str);

//void	ft_putnbr_fd(int c, int fd);
//void	ft_putnbr_fd(int n, int fd);

//int		ft_strcmp(const char *s1, const char *s2);
//int		ft_strcmp(char *s1, char *s2);

/*EXTRA LILLY*/
int		ft_isdouble(char *nbr);
char	*ft_str_lower(char *s);
char	*ft_str_upper(char *s);
int		ft_arrlen(char **s);
char	*ft_strjoin_free_both(char *s1, char *s2);
char	*ft_strjoin_free_one(char *s1, const char *s2);
int		ft_printf(const char *format, ...);
int		ft_printchar(int c);
int		ft_printstr(char *s);
int		ft_printnbr(char specifier, long int nbr, int base);
int		ft_printptr(void *ptr);
int		ft_decideformat(va_list args, const char *format, int i);
int		ft_white(const char *s);
double	ft_atof(char *s);
int		ft_isalpha_extend(int n);
int		ft_isprint_extend(int n);
int		ft_isascii_extend(int n);
void	ft_free_double(char **smth);
void	ft_print_array(char **arr);
int		ft_strcmp_org(const char *s1, const char *s2);
bool	ft_strnstr_bool(const char *big, const char *lil, int start, int len);

char	*get_next_line(int fd);
char	*ft_buf(char *buf, int *x);
char	*ft_next(char *buf, int fd);
char	*ft_rest(int x, char *buf);

/*EXTRA MEHRAS*/
t_list	*ft_lstnew(void *content);
void	ft_lstadd_front(t_list **alst, t_list *new);
int		ft_lstsize(t_list *lst);
t_list	*ft_lstlast(t_list *lst);
void	ft_lstadd_back(t_list **alst, t_list *new);
void	ft_lstdelone(t_list *lst, void (*del)(void*));
void	ft_lstclear(t_list **lst, void (*del)(void *));
void	ft_lstiter(t_list *lst, void (*f)(void *));
t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *));
char	*ft_strcat(char *dst, char *src);
size_t	ft_strlen_2d(char **in);
char	**ft_realloc_2d(char **in, int add);
void	ft_free_2d(char **in);
char	*ft_strncpy(char *dest, char *src, int n);

#endif