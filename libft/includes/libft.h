/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   libft.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: lskrauci <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/01/12 14:31:06 by lskrauci      #+#    #+#                 */
/*   Updated: 2019/01/12 14:31:09 by lskrauci      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H
# define BUFF_SIZE 5
# include <string.h>
# include <stdlib.h>
# include <unistd.h>
# include "libft.h"
# include <stdarg.h>
# include <wchar.h>
# include <limits.h>
# define CS	conversion_specifier

typedef struct		s_gnl
{
	int				fd;
	char			*store_buffer;
	char			read_buffer[BUFF_SIZE + 1];
	int				new_start;
	int				blocker;
	int				read_val;
	struct s_gnl	*next;
}					t_gnl;

typedef struct		s_list
{
	void			*content;
	size_t			content_size;
	struct s_list	*next;
}					t_list;

union				u_val
{
	char			character;
	char			*string;
	void			*address;
	int				number;
	unsigned int	u_number;
	float			floating;
};

typedef	struct		s_node
{
	union u_val		values;
	char			flags[6];
	int				field_width;
	int				precision;
	char			length[3];
	char			conversion_specifier;
	char			*error;
	const char		*format;
	int				flag_pos;
	struct s_node	*next;
}					t_node;

int					get_next_line(const int fd, char **line);
void				*ft_memset(void *b, int c, size_t len);
void				ft_bzero(void *s, size_t n);
void				*ft_memcpy(void *dst, const void *src, size_t n);
void				*ft_memccpy(void *dst, const void *src, int c, size_t n);
void				*ft_memmove(void *dst, const void *src, size_t len);
void				*ft_memchr(const void *s, int c, size_t n);
int					ft_memcmp(const void *s1, const void *s2, size_t n);
size_t				ft_strlen(const char *s);
char				*ft_strdup(const char *s1);
char				*ft_strcpy(char *dst, const char *src);
char				*ft_strncpy(char *dst, const char *src, size_t len);
char				*ft_strcat(char *s1, const char *s2);
char				*ft_strncat(char *s1, const char *s2, size_t n);
size_t				ft_strlcat(char *dst, const char *src, size_t size);
char				*ft_strchr(const char *s, int c);
char				*ft_strrchr(const char *s, int c);
char				*ft_strstr(const char *haystack, const char *needle);
char				*ft_strnstr(const char *haystack, const char *needle,
					size_t len);
int					ft_strcmp(const char *s1, const char *s2);
int					ft_strncmp(const char *s1, const char *s2, size_t n);
int					ft_atoi(const char *str);
int					ft_isalpha(int c);
int					ft_isdigit(int c);
int					ft_isalnum(int c);
int					ft_isascii(int c);
int					ft_isprint(int c);
int					ft_toupper(int c);
int					ft_tolower(int c);
void				*ft_memalloc(size_t size);
void				ft_memdel(void **ap);
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
char				*ft_strtrim(char const *s);
char				**ft_strsplit(char const *s, char c);
char				**ft_strsplit2(char const *s, char c);
char				*ft_itoa(int n);
void				ft_putchar(char c);
void				ft_putstr(char const *s);
void				ft_putendl(char const *s);
void				ft_putnbr(int n);
void				ft_putchar_fd(char c, int fd);
void				ft_putstr_fd(char const *s, int fd);
void				ft_putendl_fd(char const *s, int fd);
void				ft_putnbr_fd(int n, int fd);
t_list				*ft_lstnew(void const *content, size_t content_size);
void				ft_lstdelone(t_list **alst, void (*del)(void *, size_t));
void				ft_lstdel(t_list **alst, void (*del)(void *, size_t));
void				ft_lstadd(t_list **alst, t_list *new);
void				ft_lstiter(t_list *lst, void (*f)(t_list *elem));
t_list				*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem));
int					ft_printf(const char *format, ...);
int					ft_flags(t_node *node, const char *format, int *i,
					va_list ap);
int					ft_field_width(t_node *node, va_list ap,
					int *i, int check);
int					ft_precision(t_node *node, va_list ap, int *i,
					int check);
int					ft_length(t_node *node, const char *f, int *i, int check);
int					ft_conversion_specifier(t_node *node, const char *format,
					int *i);
t_node				*ft_origin_node(const char *format, int *i, va_list ap);
int					ft_add_node(t_node *head, const char *format, int *i,
					va_list ap);
t_node				*ft_extract(const char *format, va_list ap);
void				ft_info_node(t_node *head);
int					ft_print_char(t_node *node, int c);
int					ft_print_str(t_node *node, char *str);
int					ft_print_ptr(t_node *node, void *address);
int					ft_print_num(t_node *node, long long num);
int					ft_print_oct(t_node *node, unsigned long long num);
int					ft_print_unum(t_node *node, unsigned long long num);
int					ft_print_hex(t_node *node, unsigned long long num,
					int capital);
int					ft_print_f(t_node *node, double num, int leftover);
void				ft_puthex(t_node *node, unsigned long long n,
					int capital);
void				ft_putoct(t_node *node, unsigned long long n);
void				ft_putunum(t_node *node, unsigned long long n);
void				ft_putdi(t_node *node, long long n);
void				ft_putfloat(t_node *node, double n, int leftover);
int					ft_print_percent(t_node *node);
int					ft_print_invalid(t_node *node);
int					ft_print_wide_str(t_node *node, wchar_t *str);
int					ft_wchar(t_node *node, unsigned int c);
size_t				ft_wchar_strlen(wchar_t *s);
int					ft_wchar_putnstr(t_node *node, const wchar_t *s1,
					int wlen);
size_t				ft_wchar_bytes(wchar_t *s);
void				ft_free_list(t_node *head);
int					ft_return_hex(int len, t_node *node);
char				ft_fill_hex(t_node *node);
char				ft_fill_float(t_node *node);
int					ft_return_float(int len, t_node *node);
int					ft_return_oct(int len, t_node *node);
char				ft_fill_oct(t_node *node);
char				ft_fill_di(t_node *node);
int					ft_return_di(int len, t_node *node);
void				ft_compensate_num(t_node *node, long long num);
int					ft_num_len(t_node *node, long long num);
size_t				ft_wchar_size(wchar_t c);
int					ft_num_width(int num);
void				ft_field_width2(t_node *node, va_list ap, int *i,
					int *pos);
void				ft_precision2(t_node *node, va_list ap, int *i);
#endif
