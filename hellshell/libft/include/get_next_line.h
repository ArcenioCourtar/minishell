/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_next_line.h                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: ovan-rhe <ovan-rhe@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/25 13:04:00 by ovan-rhe      #+#    #+#                 */
/*   Updated: 2023/04/03 16:51:44 by ovan-rhe      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <limits.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

char	*get_next_line(int fd);
char	*read_to_stash(int fd, char *stash);
char	*stash_to_line(char *stash);
char	*next_call_stash(char *stash);

char	*ft_strjoinfree(char *s1, char *s2);
int		newline_checker(char *str);
char	*copy_stash_to_line(char *str, char *stash);
int		return_line_len(char *stash);

#endif