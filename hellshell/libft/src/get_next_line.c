/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_next_line.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: ovan-rhe <ovan-rhe@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/11/07 17:42:49 by ovan-rhe      #+#    #+#                 */
/*   Updated: 2023/04/03 16:25:03 by ovan-rhe      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*get_next_line(int fd)
{
	static char	*stash[42];
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	stash[fd] = read_to_stash(fd, stash[fd]);
	if (!stash[fd])
		return (NULL);
	line = stash_to_line(stash[fd]);
	if (!line)
	{
		free(stash[fd]);
		stash[fd] = NULL;
		return (NULL);
	}
	stash[fd] = next_call_stash(stash[fd]);
	if (!stash[fd])
		return (NULL);
	return (line);
}

char	*read_to_stash(int fd, char *stash)
{
	int		bytes_read;
	char	*buf;

	bytes_read = 1;
	buf = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buf)
		return (NULL);
	while (newline_checker(stash) < 0 && bytes_read != 0)
	{
		bytes_read = read(fd, buf, BUFFER_SIZE);
		if (bytes_read == -1)
		{
			free(stash);
			free(buf);
			stash = NULL;
			return (NULL);
		}
		buf[bytes_read] = '\0';
		stash = ft_strjoinfree(stash, buf);
		if (!stash)
			break ;
	}
	free(buf);
	return (stash);
}

char	*stash_to_line(char *stash)
{
	char	*str;
	int		line_len;

	line_len = return_line_len(stash);
	if (line_len == 0)
		return (NULL);
	str = (char *)malloc(sizeof(char) * (line_len + 1));
	if (!str)
		return (NULL);
	str = copy_stash_to_line(str, stash);
	return (str);
}

char	*next_call_stash(char *stash)
{
	char	*str;
	int		start;
	int		i;

	i = 0;
	while (stash[i] != '\n' && stash[i])
		i++;
	if (stash[i] == '\n')
		start = i + 1;
	while (stash[i])
		i++;
	str = (char *)malloc(sizeof(char) * (i - start + 1));
	if (!str)
	{
		free(stash);
		return (NULL);
	}
	i = 0;
	while (stash[start])
		str[i++] = stash[start++];
	str[i] = '\0';
	free(stash);
	return (str);
}
