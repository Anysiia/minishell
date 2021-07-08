/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmorel-a <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/07 12:01:03 by cmorel-a          #+#    #+#             */
/*   Updated: 2021/07/08 12:11:51 by cmorel-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H
# include <stdlib.h>
# include <unistd.h>
# include <errno.h>
# include <limits.h>

# define OVF_INT 214748364
# define OVF_LONG 922337203685477580

void			*ft_memset(void *b, int c, size_t len);
void			ft_bzero(void *s, size_t n);
void			*ft_memcpy(void *dst, const void *src, size_t n);
void			*ft_memccpy(void *dst, const void *src, int c, size_t n);
void			*ft_memmove(void *dst, const void *src, size_t len);
void			*ft_memchr(const void *s, int c, size_t n);
int				ft_memcmp(const void *s1, const void *s2, size_t n);
size_t			ft_strlen(const char *str);
size_t			ft_strlen_to_char(const char *str, const char c);
size_t			ft_strlen_to_charset(const char *str, const char *charset);
int				ft_isalpha(int c);
int				ft_isdigit(int c);
int				ft_isalnum(int c);
int				ft_isascii(int c);
int				ft_isprint(int c);
int				ft_isspace(int c);
int				ft_toupper(int c);
int				ft_tolower(int c);
int				ft_test_set(const char c, const char *charset);
int				ft_charset_in_str(const char *charset, const char *str);
char			*ft_strchr(const char *s, int c);
char			*ft_strrchr(const char *s, int c);
int				ft_strcmp(const char *s1, const char *s2);
int				ft_strncmp(const char *s1, const char *s2, size_t n);
size_t			ft_strlcpy(char *dst, const char *src, size_t dstsize);
size_t			ft_strlcat(char *dst, const char *src, size_t dstsize);
char			*ft_strnstr(const char *str, const char *s, size_t len);
int				ft_atoi(const char *str);
long int		ft_atol(const char *str);
long long int	ft_atoll(const char *str);
void			*ft_calloc(size_t count, size_t size);
char			*ft_strdup(const char *s1);
char			*ft_strcdup(const char *str, char c);
char			*ft_strndup(const char *s1, size_t size);
char			*ft_substr(char const *s, unsigned int start, size_t len);
char			*ft_strjoin(char const *s1, char const *s2);
char			*ft_strjoin_free_s1(char *s1, const char *s2);
char			*ft_strjoin_free_s2(const char *s1, char *s2);
char			*ft_strjoin_free_all(char *s1, char *s2);
char			*ft_strnew(size_t size);
char			*ft_strtrim(char const *s1, char const *set);
char			**ft_split(char const *s, char c);
char			**ft_split_charset(const char *s, const char *charset);
void			ft_freestr(char **string);
void			ft_strswap(char **s1, char **s2);
char			**ft_free_tab(char **tabl);
size_t			ft_len_tab(char **tabl);
char			*ft_itoa(int n);
int				ft_check_base(char *base);
char			*ft_itoa_base_unsigned(unsigned int n, char *base);
char			*ft_itoa_base_long(long long int n, char *base);
char			*ft_strmapi(char const *s, char (*f)(unsigned int, char));
void			ft_putchar(char c);
void			ft_putchar_fd(char c, int fd);
void			ft_putstr(const char *s);
void			ft_putstr_fd(const char *s, int fd);
void			ft_putendl(const char *s);
void			ft_putendl_fd(const char *s, int fd);
void			ft_putnbr_fd(int n, int fd);
void			ft_putnbr(int n);
int				ft_str_check_ending(const char *file, const char *type);
int				ft_char_in_set(const char c, const char *str);
int				get_next_line(int fd, char **line);

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}				t_list;
t_list			*ft_lstnew(void *content);
void			ft_lstadd_front(t_list **alst, t_list *new);
int				ft_lstsize(t_list *lst);
t_list			*ft_lstlast(t_list *lst);
void			ft_lstadd_back(t_list **alst, t_list *new);
void			ft_lstdelone(t_list *lst, void (*del)(void*));
void			ft_lstclear(t_list **lst, void (*del)(void*));
void			ft_lstiter(t_list *lst, void (*f)(void *));
#endif
