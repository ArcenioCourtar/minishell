/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_memmove.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: ovan-rhe <ovan-rhe@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/12 14:22:15 by ovan-rhe      #+#    #+#                 */
/*   Updated: 2022/10/18 18:46:27 by ovan-rhe      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief Copies 'len' bytes from string 'src' to string 'dst'. The two strings
 * may overlap; the copy is always done in a non-destructive manner.
 * @param dst The destination string
 * @param src The source string
 * @param len The number of bytes to copy
 * @return A pointer to the destination string
 */
void	*ft_memmove(void *dst, const void *src, size_t len)
{
	char	*s;
	char	*d;
	size_t	i;

	s = (char *)src;
	d = (char *)dst;
	i = 0;
	if (!s && !d)
		return (0);
	if (dst > src)
	{
		while (len-- > 0)
			d[len] = s[len];
	}
	else
	{
		while (i < len)
		{
			d[i] = s[i];
			i++;
		}
	}
	return (dst);
}
