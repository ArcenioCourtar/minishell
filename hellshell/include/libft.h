/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   libft.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: ovan-rhe <ovan-rhe@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/06 14:18:37 by ovan-rhe      #+#    #+#                 */
/*   Updated: 2023/05/08 16:58:52 by ovan-rhe      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <stdlib.h>
# include <unistd.h>
# include "get_next_line.h"
# include "ft_printf.h"

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}					t_list;

void	free_double_array(char **d_arr);

int		ft_abs(int i);

void	ft_error(int errnum, const char *error_msg);

// Converts input string to an int
int		ft_atoi(const char *str);
// Converts input string to a long
long	ft_atol(const char *str);
int		ft_atoi_safe(const char *str, int *nbr);
// Set memory block of size n at address s to 0
void	ft_bzero(void *s, size_t n);
// Malloc, then set the malloced space to 0
void	*ft_calloc(size_t count, size_t size);
// Check if input character is alphanumeric
int		ft_isalnum(int c);
// Check if input character is part of the alphabet
int		ft_isalpha(int c);
// Check if input character is part of the standard ASCII table
int		ft_isascii(int c);
// Check if input character is a digit
int		ft_isdigit(int c);
// Check if input character is printable ('space' is a printable char)
int		ft_isprint(int c);
// Check if input character is a whitespace ('\f', '\n', '\r', '\t', '\v', ' ')
int		ft_iswhitespace(int c);
// Scans n bytes of memory for first instance of c. (interpr as uchar)
void	*ft_memchr(const void *s, int c, size_t n);
// memcmp is strcmp without the str. xDDDDD
int		ft_memcmp(const void *s1, const void *s2, size_t n);
// Copies n bytes from src to dest. MUST NO OVERLAP. Use memmove otherwise
void	*ft_memcpy(void *dst, const void *src, size_t n);
// Copies n bytes form src to dest, areas may overlap.
void	*ft_memmove(void *dst, const void *src, size_t len);
// set the first n bytes starting from pointer s to byte value c
void	*ft_memset(void *b, int c, size_t len);
// Find c in string s. Returns ptr to first instance of c, or NULL
char	*ft_strchr(char *s, int c);
// Returns a pointer to a duplicate of string s, using malloc()
char	*ft_strdup(const char *s1);
// Concatenates string in src to the string in dst up to size - bytes (combined)
size_t	ft_strlcat(char *dst, const char *src, size_t dstsize);
// Copies string located in src into dst, up to size - 1 bytes
size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize);
// Returns character length of the string (excluding the NULL-terminator!)
size_t	ft_strlen(const char *s);
// Compares n bytes of s1 and s2 with each other, returns the difference
int		ft_strncmp(const char *s1, const char *s2, size_t n);
// Tries to find null-terminated string 'little' inside 'big'
char	*ft_strnstr(const char *haystack, const char *needle, size_t len);
// Find c in string s. Returns ptr to last instance of c, or NULL
char	*ft_strrchr(const char *s, int c);
// Return lowercase version of uppercase ASCII letter
int		ft_tolower(int c);
// Return uppercase version of lowercase ASCII letter
int		ft_toupper(int c);

// Allocates and returns a substring from s, start at start with max size len
char	*ft_substr(char const *s, unsigned int start, size_t len);
// Allocates and returns a new string, concatenating s1 and s2
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_strjoinfree(char *s1, char *s2);
// Allocates and return a string, trimming of first/last instance of 'set'
char	*ft_strtrim(char const *s1, char const *set);
// Allocates and returns an array of strings. splitting string s with delim c
char	**ft_split(char const *s, char c);
// Converts an int to string which is allocated and returned
char	*ft_itoa(int n);
// Write a character to a specific fd
void	ft_putchar_fd(char c, int fd);
// Write a string to a specific fd
void	ft_putstr_fd(char *s, int fd);
// Write a string with a newline at the end to a specific fd
void	ft_putendl_fd(char *s, int fd);
// Write the number 'n' to a specific fd
void	ft_putnbr_fd(int n, int fd);
// perform function 'f' on char 's'
void	ft_striteri(char *s, void (*f)(unsigned int, char*));
// perform function 'f' on all characters of string 's', which then gets allocd
char	*ft_strmapi(char const *s, char (*f)(unsigned int, char));

t_list	*ft_lstnew(void *content);
void	ft_lstadd_front(t_list **lst, t_list *new);
int		ft_lstsize(t_list *lst);
t_list	*ft_lstlast(t_list *lst);
void	ft_lstadd_back(t_list **lst, t_list *new);
void	ft_lstdelone(t_list *lst, void (*del)(void*));
void	ft_lstclear(t_list **lst, void (*del)(void*));
void	ft_lstiter(t_list *lst, void (*f)(void *));
t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *));

#endif