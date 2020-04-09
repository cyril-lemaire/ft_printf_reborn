/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clemaire <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/17 12:46:42 by clemaire          #+#    #+#             */
/*   Updated: 2020/04/08 12:35:41 by cyrlemai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H
# include <stddef.h>

typedef struct	s_list
{
	void			*content;
	struct s_list	*next;
}				t_list;

int				ft_strncmp(const char *s1, const char *s2, size_t n);
size_t			ft_strlen(const char *s);
char			*ft_strdup(const char *s);
void			ft_bzero(void *s, size_t n);
void			*ft_memchr(const void *s, int c, size_t n);
void			*ft_memccpy(void *dst, const void *src, int c, size_t n);
void			*ft_memcpy(void *dst, const void *src, size_t n);
void			*ft_memmove(void *dst, const void *src, size_t len);
void			*ft_memset(void *b, int c, size_t len);
int				ft_memcmp(const void *s1, const void *s2, size_t n);
char			*ft_strchr(const char *s, int c);
char			*ft_strnstr(const char *haystack, const char *needle,
					size_t len);
char			*ft_strrchr(const char *s, int c);
int				ft_atoi(const char *str);
int				ft_isascii(int c);
int				ft_isdigit(int c);
int				ft_isalpha(int c);
int				ft_islower(int c);
int				ft_isupper(int c);
int				ft_isprint(int c);
int				ft_isalnum(int c);
int				ft_tolower(int c);
int				ft_toupper(int c);
char			*ft_strmapi(char const *s, char (*f)(unsigned int, char));
char			*ft_strjoin(char const *s1, char const *s2);
char			*ft_strtrim(char const *s, char const *charset);
char			**ft_split(char const *s, char c);
char			*ft_itoa(int n);
void			ft_putchar_fd(char c, int fd);
void			ft_putstr_fd(char const *s, int fd);
void			ft_putendl_fd(char const *s, int fd);
void			ft_putnbr_fd(int n, int fd);
char			*ft_stradd(const char *dest, const char *src);
void			*ft_calloc(size_t count, size_t size);
char			*ft_substr(const char *s, unsigned int start, size_t len);
size_t			ft_strlcpy(char *dst, const char *src, size_t size);
size_t			ft_strlcat(char *dst, const char *src, size_t size);
char			*ft_strcpy(char *dst, const char *src);
char			*ft_strncpy(char *dst, const char *src, size_t len);
int				ft_strcmp(const char *s1, const char *s2);
size_t			ft_strnlen(const char *s, size_t max_len);
char			*ft_strcat(char *s1, const char *s2);
char			*ft_strncat(char *s1, const char *s2, size_t n);
char			*ft_strstr(const char *haystack, const char *needle);
void			*ft_memalloc(size_t size);
void			ft_memdel(void **ap);
char			*ft_strnew(size_t size);
void			ft_strdel(char **as);
void			ft_strclr(char *s);
void			ft_striter(char *s, void (*f)(char *));
void			ft_striteri(char *s, void (*f)(unsigned int, char *));
char			*ft_strmap(char const *s, char (*f)(char));
int				ft_strequ(char const *s1, char const *s2);
int				ft_strnequ(char const *s1, char const *s2, size_t n);
void			ft_putchar(char c);
void			ft_putstr(char const *s);
void			ft_putendl(char const *s);
void			ft_putnbr(int n);
int				ft_isspace(int c);
int				ft_mod(int n, int b);
int				ft_abs(int n);
double			ft_min(double a, double b);
double			ft_max(double a, double b);
void			*ft_realloc(void *ptr, size_t old_size, size_t new_size);
t_list			*ft_lstnew(void *content);
void			ft_lstdelone(t_list *alst, void (*del)(void *));
void			ft_lstclear(t_list **alst, void (*del)(void *));
t_list			*ft_lstadd_front(t_list **alst, t_list *new);
void			ft_lstiter(t_list *lst, void (*f)(void *elem));
t_list			*ft_lstmap(t_list *lst, void *(*f)(void *elem),
					void (*del)(void*));
t_list			*ft_lstadd_back(t_list **alst, const t_list *new);
t_list			*ft_lstgetindex(const t_list *lst, size_t index);
int				ft_lstdelindex(t_list **alst, size_t index,
					void (*del)(void*));
int				ft_lstdelnext(t_list *node, void (*del)(void*));
int				ft_lstsize(t_list *lst);
t_list			*ft_lstlast(t_list *lst);
char			*ft_stradd(const char *dest, const char *src);
char			*ft_stracat(char *dest, const char *src);
size_t			ft_wcslen(const wchar_t *s);
int				ft_wctomb(char *s, wchar_t wchar);
int				ft_wclen(wchar_t wc);
long double		ft_intpow(long double nb, int power);

#endif
