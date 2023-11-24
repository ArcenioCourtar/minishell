/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_memcmp.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: ovan-rhe <ovan-rhe@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/10 14:10:16 by ovan-rhe      #+#    #+#                 */
/*   Updated: 2022/10/18 18:34:28 by ovan-rhe      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief Compares byte string s1 against byte string s2. Both strings are
 * assumed to be n bytes long.
 * @param s1 The first string to compare
 * @param s2 The second string to compare
 * @param n The number of bytes to compare
 * @return An integer greater than, equal to, or less than 0, according as the
 * string s1 is greater than, equal to, or less than the string s2. The
 * comparison is done using unsigned characters, so that `\200' is greater than
 * `\0'.
 */
int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t			i;
	unsigned char	*str1;
	unsigned char	*str2;

	str1 = (unsigned char *)s1;
	str2 = (unsigned char *)s2;
	i = 0;
	while (i < n)
	{
		if (str1[i] != str2[i])
			return (str1[i] - str2[i]);
		i++;
	}
	return (0);
}
