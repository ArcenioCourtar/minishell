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

static size_t	word_counter(char const *s, char c);
static int		insert_word(char const *s, char c, char **str, size_t w_count);

char	**ft_split(char const *s, char c)
{
	char	**str_array;
	size_t	word_count;

	word_count = word_counter(s, c);
	str_array = (char **)malloc(sizeof(char *) * (word_count + 1));
	if (!str_array)
		return (NULL);
	if (!insert_word(s, c, str_array, word_count))
	{
		free_double_array(str_array);
		return (NULL);
	}
	return (str_array);
}

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

static int	insert_word(char const *s, char c, char **str, size_t w_count)
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
			str[j] = ft_substr(s, start, i - start);
			if (str[j] == 0)
				return (0);
			j++;
		}
	}
	str[j] = 0;
	return (1);
}
