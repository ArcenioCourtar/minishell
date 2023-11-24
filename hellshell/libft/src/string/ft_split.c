/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_split.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: ovan-rhe <ovan-rhe@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/14 14:56:53 by ovan-rhe      #+#    #+#                 */
/*   Updated: 2023/04/11 14:22:19 by ovan-rhe      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief Counts the number of words in a string
 * @param s The string to count the words in
 * @param c The character to use as a delimiter
 * @return The number of words in the string
 */
static size_t	word_counter(char const *s, char c)
{
	size_t	count;
	size_t	i;

	count = 0;
	i = 0;
	while (s && s[i])
	{
		if (s[i] != c)
		{
			count++;
			while (s[i] != c && s[i])
				i++;
		}
		else
			i++;
	}
	return (count);
}

/**
 * @brief Inserts words delimited by the character c into an array of strings
 * @param s The string to insert the words from
 * @param c The character to use as a delimiter
 * @param str The array of strings to insert the words into
 * @param w_count The number of words in the string
 * @return 1 on success, 0 on failure
 */
static int	insert_word(char const *s, char c, char **str_arr, size_t w_count)
{
	size_t	i;
	size_t	j;
	size_t	start;

	i = -1;
	j = 0;
	while (j < w_count)
	{
		if (s[++i] != c)
		{
			start = i;
			while (s[i] != c && s[i] != '\0')
				i++;
			str_arr[j] = ft_substr(s, start, i - start);
			if (str_arr[j] == 0)
				return (0);
			j++;
		}
	}
	str_arr[j] = 0;
	return (1);
}

/**
 * @brief Splits a string into an array of strings
 * @param s The string to split
 * @param c The character to use as a delimiter
 * @return The array of strings
 */
char	**ft_split(char const *s, char c)
{
	char	**str_arr;
	size_t	word_count;

	word_count = word_counter(s, c);
	str_arr = (char **)malloc(sizeof(char *) * (word_count + 1));
	if (!str_arr)
		return (NULL);
	if (!insert_word(s, c, str_arr, word_count))
	{
		free_double_array(str_arr);
		return (NULL);
	}
	return (str_arr);
}
