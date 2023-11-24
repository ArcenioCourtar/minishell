/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strchr.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: ovan-rhe <ovan-rhe@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/06 14:47:36 by ovan-rhe      #+#    #+#                 */
/*   Updated: 2022/10/18 18:22:45 by ovan-rhe      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief Locates the first occurrence of c (converted to a char) in the string
 * pointed to by s. The terminating null character is considered to be part of
 * the string; therefore if c is `\0', the functions locate the terminating `\0'.
 * @param s The string to search
 * @param c The character to search for
 * @return A pointer to the located character, or NULL if the character does not
 * appear in the string
 */
char	*ft_strchr(char *s, int c)
{
	size_t	i;
	size_t	len_s;

	i = 0;
	len_s = ft_strlen(s);
	while (i <= len_s)
	{
		if (s[i] == (char)c)
			return (&s[i]);
		else
			i++;
	}
	return (NULL);
}
