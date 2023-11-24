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

#include "get_next_line.h"

/**
 * @brief Reads from a file descriptor and stores the read data in a stash
 * @param fd The file descriptor to read from
 * @param stash The stash to store the read data in
 * @return The stash with the read data. NULL if the allocation fails
 */
static char	*read_to_stash(int fd, char *stash)
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

/**
 * @brief Copies the data from the stash to a line
 * @param stash The stash to copy from
 * @return The line with the copied data. NULL if the allocation fails
 */
static char	*stash_to_line(char *stash)
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

/**
 * @brief Copies the data from the stash to a line
 * @param stash The stash to copy from
 * @return The line with the copied data. NULL if the allocation fails
 */
static char	*next_call_stash(char *stash)
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

/**
 * @brief Reads a line from a file descriptor
 * @param fd The file descriptor to read from
 * @return The line that was read. NULL if the allocation fails
 */
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
