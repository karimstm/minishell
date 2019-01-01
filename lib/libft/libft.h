/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amoutik <abdelkarimoutik@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/04 12:57:03 by amoutik           #+#    #+#             */
/*   Updated: 2018/12/31 14:54:08 by amoutik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H
# include <string.h>
# include <stdlib.h>
# include <unistd.h>

typedef struct	s_list
{
	void			*content;
	size_t			content_size;
	struct s_list	*next;
}				t_list;
int				ft_isspace(int c);
void			ft_putchar(char c);
void			ft_putchar_fd(char c, int fd);
void			ft_putstr(char const *s);
size_t			ft_strlen(const char *str);
size_t			ft_strnlen(const char *s, size_t maxlen);
int				ft_isalpha(int c);
int				ft_isdigit(int c);
void			ft_bzero(void *s, size_t n);
void			ft_putstr_fd(char const *s, int fd);
int				ft_strncmp(const char *s1, const char *s2, unsigned int n);
void			*ft_memset(void *b, int c, size_t len);
void			*ft_memcpy(void *dest, const void *src, size_t n);
void			*ft_memalloc(size_t size);
char			*ft_strnew(size_t size);
void			ft_putendl(char const *s);
void			*ft_memccpy(void *dest, const void *src, int c, size_t n);
void			*ft_memchr(const void *s, int c, size_t n);
void			*ft_memmove(void *dest, const void *src, size_t n);
int				ft_memcmp(const void *s1, const void *s2, size_t n);
void			ft_putnbr(int nb);
char			*ft_strdup(const char *src);
char			*ft_strcat(char *dest, const char *src);
char			*ft_strncat(char *dest, const char *src, int nb);
size_t			ft_strlcat(char *dest, const char *src, size_t size);
char			*ft_strchr(const char *s, int c);
char			*ft_strrchr(const char *s, int c);
char			*ft_strstr(const char *str, const char *to_find);
char			*ft_strnstr(const char *haystack, const char *needle, size_t n);
int				ft_strcmp(const char *s1, const char *s2);
int				ft_atoi(const char *str);
char			*ft_itoa(int n);
int				ft_isalnum(int c);
int				ft_isascii(int c);
int				ft_isprint(int c);
int				ft_toupper(int c);
int				ft_tolower(int c);
void			ft_memdel(void **ap);
void			ft_strdel(char **as);
void			ft_strclr(char *s);
char			*ft_strcpy(char *dest, const char *src);
char			*ft_strncpy(char *dest, const char *src, size_t len);
void			ft_striter(char *s, void (*f)(char *));
void			ft_striteri(char *s, void (*f)(unsigned int, char *));
char			*ft_strmap(char const *s, char (*f)(char));
char			*ft_strmapi(char const *s, char (*f)(unsigned int, char));
int				ft_strequ(char const *s1, char const *s2);
int				ft_strnequ(char const *s1, char const *s2, size_t n);
char			*ft_strsub(char const *s, unsigned int start, size_t n);
char			*ft_strjoin(char const *s1, char const *s2);
void			ft_putendl_fd(char const *s, int fd);
size_t			ft_strnlen(const char *s, size_t maxlen);
char			**ft_strsplit(char const *s, char c);
size_t			ft_strspn(const char *s1, const char *s2);
size_t			ft_strcspn(const char *s1, const char *s2);
t_list			*ft_lstnew(void const *content, size_t content_size);
void			ft_lstdelone(t_list **alst, void (*del)(void *, size_t));
void			ft_lstdel(t_list **alst, void (*del)(void *, size_t));
void			ft_lstadd(t_list **alst, t_list *new);
void			ft_lstiter(t_list *lst, void (*f)(t_list *elem));
t_list			*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem));
size_t			ft_strspn(const char *s, const char *charset);
size_t			ft_strcspn(const char *s, const char *charset);
char			*ft_strtrim(char const *s);
void			ft_putnbr_fd(int n, int fd);
char			*ft_strtok(char *str, const char *delim);

#endif
