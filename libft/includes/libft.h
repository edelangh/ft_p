/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edelangh <edelangh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/03 14:33:53 by edelangh          #+#    #+#             */
/*   Updated: 2015/01/31 17:54:45 by edelangh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <string.h>

# define C_RED "\033[22;31m"
# define C_GREEN "\033[22;32m"
# define C_BLUE "\033[22;34m"
# define C_MAGENTA "\033[22;35m"
# define C_YELLOW "\033[01;33m"
# define C_PINK "\033[01;35m"
# define C_CYAN "\033[01;36m"
# define C_WHITE "\033[01;37m"
# define C_GRAY "\033[01;37m"
# define C_BLINK "\033[5m"
# define C_EOC "\033[22;37m"

typedef struct timespec	t_timespec;

typedef struct		s_list
{
	void			*content;
	size_t			content_size;
	struct s_list	*next;
}					t_list;

void				ft_bzero(void *s, size_t n);
void				*ft_memccpy(void *dst, const void *src, int c, size_t n);
int					ft_memcmp(const void *s1, const void *s2, size_t n);
void				*ft_memcpy(void *dst, const void *src, size_t n);
void				*ft_memset(void *b, int c, size_t len);
void				*ft_memchr(const void *s, int c, size_t n);
void				*ft_memmove(void *dst, const void *src, size_t len);
void				ft_memdel(void **ap);
void				*ft_memdup(const void *s1, size_t len);
void				ft_realloc(void **ptr, size_t slen, size_t nlen);
void				*ft_memalloc(size_t size);
void				*ft_malloc(size_t size);
int					ft_free(void *a);

size_t				ft_tablen(void **tab);
int					ft_freetab(char **tab);

void				ft_swap(void **a, void **b);
void				ft_swap_int(int *a, int *b);
void				ft_swap_double(double *a, double *b);

int					ft_atoi(const char *src);
double				ft_atof(const char *src);
size_t				ft_strlcat(char *dst, const char *src, size_t size);
size_t				ft_strlen(const char *s1);
size_t				ft_len_untill(const char *str, char c);
char				*ft_strdup(const char *s1);
char				*ft_strcpy(char *dst, const char *src);
char				*ft_strncpy(char *dst, const char *src, size_t n);
char				*ft_strcat(char *s1, const char *s2);
char				*ft_strncat(char *dest, const char *src, size_t n);
size_t				ft_strlcpy(char *dst, const char *src, size_t size);
char				*ft_strchr(const char *s, int c);
int					ft_strcmp(const char *s1, const char *s2);
int					ft_strncmp(const char *s1, const char *s2, size_t n);
char				*ft_strncpy(char *dst, const char *src, size_t n);
char				*ft_strnstr(const char *s1, const char *s2, size_t n);
char				*ft_strrchr(const char *s, int c);
char				*ft_strstr(const char *s1, const char *s2);
char				*ft_strnew(size_t size);
void				ft_strdel(char **as);
void				ft_strclr(char *s);
void				ft_striter(char *s, void (*f)(char *));
void				ft_striteri(char *s, void (*f)(unsigned int, char *));
char				*ft_strmap(char const *s, char (*f)(char));
char				*ft_strmapi(char const *s, char (*f)(unsigned int, char));
int					ft_strequ(char const *s1, char const *s2);
int					ft_strnequ(char const *s1, char const *s2, size_t n);
char				*ft_strsub(char const *s, unsigned int start, size_t len);
char				*ft_strjoin(char const *s1, char const *s2);
char				*ft_strfjoin(char *s1, char *s2, int a, int b);
char				*ft_strjoinnchar(char *s, int n, char c);
char				*ft_strfjoinnchar(char *s, int n, char c);
char				*ft_strinsert(char *a, char *b, int pos);
char				*ft_strfinsert(char *a, char *b, int pos, int frees);
char				*ft_strreplace(char *str, char *match, char *to);
char				*ft_strfreplace(char *str, char *match, char *to);
char				*ft_strnreplace(char *str, char *match, char *to, size_t n);
char				*ft_strrev(char *s);
size_t				ft_str_alphawash(char *str);

char				**ft_strsplit(const char *s, char c);
void				ft_lsort(char **tab, int len);
char				**ft_splitcmd(char *cmd);

char				*ft_convert_base(char *nbr, char *base_from, char *base_to);

char				*ft_strtrim(char const *s);
char				*ft_itoa(int n);
char				*ft_zutoa(size_t n);
char				*ft_lltoa(long long n);

void				ft_putchar(char c);
void				ft_putnchar(char c, int n);
void				ft_putstr(char const *c);
void				ft_putendl(char const *s);
void				ft_putnbr(int n);
void				ft_putchar_fd(char c, int fd);
void				ft_putstr_fd(char const *s, int fd);
void				ft_putendl_fd(char const *s, int fd);
void				ft_putnbr_fd(int n, int fd);

int					ft_isalnum(int c);
int					ft_isalpha(int c);
int					ft_isascii(int c);
int					ft_isdigit(int c);
int					ft_isprint(int c);
int					ft_tolower(int c);
int					ft_toupper(int c);

t_list				*ft_lstnew(void const *content, size_t content_size);
t_list				*ft_lstpush(t_list **lst, t_list *new);
void				ft_lstdelone(t_list **alst, void (*del)(void *, size_t));
void				ft_lstdel(t_list **alst, void (*del)(void *, size_t));
void				ft_lstadd(t_list **alst, t_list *new);
void				ft_lstiter(t_list *lst, void (*f)(t_list *elem));
t_list				*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem));
t_list				*ft_lstend(t_list *lst);
void				ft_lstsort(t_list *lst, int (*f)(void*, void*));
void				ft_lstmergesort(t_list **lst, int (*f)(void*, void*));
t_list				*ft_lstat(t_list *lst, size_t i);
size_t				ft_lstlen(t_list *lst);
t_list				*ft_lstcat(t_list *lst1, t_list *lst2);

size_t				ft_ntime();
float				ft_rsqrt(float number);

int					ft_rm(char *src);
#endif
