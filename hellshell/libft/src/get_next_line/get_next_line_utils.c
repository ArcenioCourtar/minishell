/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_next_line_utils.c                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: ovan-rhe <ovan-rhe@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/11/07 19:19:53 by ovan-rhe      #+#    #+#                 */
/*   Updated: 2023/04/03 16:15:03 by ovan-rhe      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

/**
 * @brief Allocates (with malloc(3)) and returns a new string, which is the
 * result of the concatenation of ’s1’ and ’s2’.
 * @param s1 The prefix string
 * @param s2 The suffix string
 * @return The new string. NULL if the allocation fails
 */
int	newline_checker(char *str)
{
	int	i;

	i = 0;
	while (str && str[i])
	{
		if (str[i] == '\n')
			return (i);
		i++;
	}
	return (-1);
}

/**
 * @brief Allocates (with malloc(3)) and returns a new string, which is the
 * result of the concatenation of ’s1’ and ’s2’.
 * @param s1 The prefix string
 * @param s2 The suffix string
 * @return The new string. NULL if the allocation fails
 */
char	*copy_stash_to_line(char *str, char *stash)
{
	int	i;

	i = 0;
	while (stash[i] && stash[i] != '\n')
	{
		str[i] = stash[i];
		i++;
	}
	if (stash[i] == '\n')
	{
		str[i] = stash[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}

/**
 * @brief Counts the number of characters in a string until a newline or null
 * @param stash The string to count
 * @return The number of characters in the string
 */
int	return_line_len(char *stash)
{
	int	i;

	i = 0;
	while (stash && stash[i] != '\0' && stash[i] != '\n')
		i++;
	if (stash[i] == '\n')
		i++;
	return (i);
}
