/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strrchr.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: ovan-rhe <ovan-rhe@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/06 16:08:50 by ovan-rhe      #+#    #+#                 */
/*   Updated: 2022/10/18 18:24:13 by ovan-rhe      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief Locates the last occurrence of c in the string pointed to by s
 * @param s The string to search
 * @param c The character to search for
 * @return A pointer to the located character, 
 * or NULL if the character does not appear in the string
 */
char	*ft_strrchr(const char *s, int c)
{
	size_t		i;
	char		*last;

	i = 0;
	last = 0;
	while (i <= ft_strlen((char *)s))
	{
		if (s[i] == (char)c)
			last = &((char *)s)[i];
		i++;
	}
	return (last);
}
